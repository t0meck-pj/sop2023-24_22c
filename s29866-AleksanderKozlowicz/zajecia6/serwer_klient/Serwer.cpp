#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>

const int PORT = 65432;
const char *LOG_FILE = "server.log";
std::ofstream logFile;

void log_message(const std::string &message) {
    logFile << message << std::endl;
    std::cout << message << std::endl;
}

void handle_client(int client_socket, struct sockaddr_in client_address) {
    try {
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);
        int client_port = ntohs(client_address.sin_port);
        std::string client_info = "Connected by " + std::string(client_ip) + ":" + std::to_string(client_port);
        log_message(client_info);

        uint32_t filename_length;
        if (recv(client_socket, &filename_length, sizeof(filename_length), 0) <= 0) {
            close(client_socket);
            return;
        }
        filename_length = ntohl(filename_length);

        char filename[filename_length + 1];
        if (recv(client_socket, filename, filename_length, 0) <= 0) {
            close(client_socket);
            return;
        }
        filename[filename_length] = '\0';
        log_message("Requested file: " + std::string(filename));

        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            int64_t file_size = -1;
            file_size = htonl(file_size);
            send(client_socket, &file_size, sizeof(file_size), 0);
            log_message("File not found: " + std::string(filename));
        } else {
            int64_t file_size = file.tellg();
            file.seekg(0, std::ios::beg);
            file_size = htonl(file_size);
            send(client_socket, &file_size, sizeof(file_size), 0);

            char buffer[4096];
            while (file.read(buffer, sizeof(buffer)).gcount() > 0) {
                send(client_socket, buffer, file.gcount(), 0);
            }
            log_message("File sent: " + std::string(filename));
        }
        close(client_socket);
        log_message("Connection closed: " + client_info);
    } catch (std::exception &e) {
        log_message(std::string("Error: ") + e.what());
    }
}

void shutdown_server(int signum) {
    log_message("Server shutdown initiated.");
    logFile.close();
    exit(0);
}

int main() {
    signal(SIGINT, shutdown_server);
    logFile.open(LOG_FILE, std::ios::app);

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

    log_message("Server started on port " + std::to_string(PORT));

    while (true) {
        sockaddr_in client_address{};
        socklen_t client_address_len = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_len);
        if (client_socket < 0) {
            perror("Accept failed");
            close(server_socket);
            exit(EXIT_FAILURE);
        }

        handle_client(client_socket, client_address);
    }

    close(server_socket);
    return 0;
}

