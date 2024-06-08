#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <algorithm>

using namespace std;

const int PORT = 8080;
const char *LOG_FILE = "server.log";
const char *FORBIDDEN_FILE = "forbidden.txt";
ofstream logFile;
unordered_map<string, string> virtual_hosts;
vector<string> forbidden_addresses;

void log_message(const string &message) {
    logFile << message << endl;
    cout << message << endl;
}

void load_forbidden_addresses() {
    ifstream infile(FORBIDDEN_FILE);
    string address;
    while (infile >> address) {
        forbidden_addresses.push_back(address);
    }
    infile.close();
}

bool is_address_forbidden(const string &address) {
    return find(forbidden_addresses.begin(), forbidden_addresses.end(), address) != forbidden_addresses.end();
}

void load_virtual_hosts() {
    virtual_hosts["www.example.com"] = "/var/www/example";
    virtual_hosts["www.test.com"] = "/var/www/test";
}

string get_host_root(const string &host) {
    if (virtual_hosts.find(host) != virtual_hosts.end()) {
        return virtual_hosts[host];
    }
    return "/var/www/default";
}

void handle_client(int client_socket, sockaddr_in client_address) {
    try {
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);
        int client_port = ntohs(client_address.sin_port);
        string client_info = "Connected by " + string(client_ip) + ":" + to_string(client_port);
        log_message(client_info);

        if (is_address_forbidden(client_ip)) {
            string response = "HTTP/1.1 403 Forbidden\r\nContent-Length: 0\r\n\r\n";
            send(client_socket, response.c_str(), response.length(), 0);
            log_message("Access forbidden: " + string(client_ip));
            close(client_socket);
            return;
        }

        char buffer[4096];
        ssize_t received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (received <= 0) {
            close(client_socket);
            return;
        }
        buffer[received] = '\0';

        string request(buffer);
        string method = request.substr(0, request.find(" "));
        string path = request.substr(request.find(" ") + 1, request.find(" ", request.find(" ") + 1) - (request.find(" ") + 1));
        string host = request.substr(request.find("Host: ") + 6, request.find("\r\n", request.find("Host: ") + 6) - (request.find("Host: ") + 6));
        host = host.substr(0, host.find("\r\n"));

        string root = get_host_root(host);
        string file_path = root + path;
        if (file_path.back() == '/') {
            file_path += "index.html";
        }

        ifstream file(file_path);
        if (!file.is_open()) {
            string response = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
            send(client_socket, response.c_str(), response.length(), 0);
            log_message("File not found: " + file_path);
        } else {
            string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
            string response = "HTTP/1.1 200 OK\r\nContent-Length: " + to_string(content.size()) + "\r\n\r\n" + content;
            send(client_socket, response.c_str(), response.length(), 0);
            log_message("File served: " + file_path);
        }

        close(client_socket);
        log_message("Connection closed: " + client_info);
    } catch (exception &e) {
        log_message(string("Error: ") + e.what());
    }
}

void shutdown_server(int signum) {
    log_message("Server shutdown initiated.");
    logFile.close();
    exit(0);
}

void handle_child_exit(int signum) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main() {
    signal(SIGINT, shutdown_server);
    signal(SIGCHLD, handle_child_exit);
    logFile.open(LOG_FILE, ios::app);

    load_forbidden_addresses();
    load_virtual_hosts();

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    log_message("Server started on port " + to_string(PORT));

    while (true) {
        sockaddr_in client_address{};
        socklen_t client_address_len = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_len);
        if (client_socket < 0) {
            perror("Accept failed");
            close(server_socket);
            exit(EXIT_FAILURE);
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            close(client_socket);
            close(server_socket);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            close(server_socket);
            handle_client(client_socket, client_address);
            exit(0);
        } else {
            close(client_socket);
        }
    }

    close(server_socket);
    return 0;
}

