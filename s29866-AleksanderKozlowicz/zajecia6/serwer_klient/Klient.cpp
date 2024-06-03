#include <iostream>
#include <fstream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

const char *HOST = "localhost";
const int PORT = 65432;

void download_file(const std::string &filename) {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    if (inet_pton(AF_INET, HOST, &server_address.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    uint32_t filename_length = htonl(filename.size());
    send(client_socket, &filename_length, sizeof(filename_length), 0);
    send(client_socket, filename.c_str(), filename.size(), 0);

    int64_t file_size;
    if (recv(client_socket, &file_size, sizeof(file_size), 0) <= 0) {
        perror("Receive failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    file_size = ntohl(file_size);

    if (file_size == -1) {
        std::cout << "File '" << filename << "' not found on server." << std::endl;
        close(client_socket);
        return;
    }

    std::ofstream output_file(filename, std::ios::binary);
    char buffer[4096];
    int64_t remaining = file_size;
    while (remaining > 0) {
        ssize_t len = recv(client_socket, buffer, std::min(static_cast<int64_t>(sizeof(buffer)), remaining), 0);
        if (len <= 0) {
            perror("Receive failed");
            break;
        }
        output_file.write(buffer, len);
        remaining -= len;
    }

    if (remaining == 0) {
        std::cout << "File '" << filename << "' downloaded successfully." << std::endl;
    } else {
        std::cerr << "Download incomplete." << std::endl;
    }

    close(client_socket);
}

int main() {
    std::string filename;
    std::cout << "Enter the filename to download: ";
    std::cin >> filename;
    download_file(filename);
    return 0;
}

