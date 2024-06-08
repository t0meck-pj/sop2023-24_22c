#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int server_socket;

void handle_sigint(int sig) {
    close(server_socket);
    printf("Serwer został zamknięty.\n");
    exit(0);
}

void log_client_info(struct sockaddr_in client_addr, char *filename) {
    FILE *log_file = fopen("server_log.txt", "a");
    if (log_file == NULL) {
        perror("Nie można otworzyć pliku logu");
        return;
    }

    time_t now;
    time(&now);
    fprintf(log_file, "Czas: %s", ctime(&now));
    fprintf(log_file, "Połączony z: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    fprintf(log_file, "Plik: %s\n\n", filename);

    fclose(log_file);
}

void handle_client(int client_socket, struct sockaddr_in client_addr) {
    int filename_length;
    char filename[BUFFER_SIZE];

    // Odbieranie długości nazwy pliku
    read(client_socket, &filename_length, sizeof(filename_length));
    filename_length = ntohl(filename_length);

    // Odbieranie nazwy pliku
    read(client_socket, filename, filename_length);
    filename[filename_length] = '\0';

    // Logowanie informacji o kliencie
    log_client_info(client_addr, filename);

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        int file_size = htonl(-1);
        write(client_socket, &file_size, sizeof(file_size));
    } else {
        fseek(file, 0, SEEK_END);
        int file_size = ftell(file);
        fseek(file, 0, SEEK_SET);

        file_size = htonl(file_size);
        write(client_socket, &file_size, sizeof(file_size));

        char buffer[BUFFER_SIZE];
        int bytes_read;
        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
            write(client_socket, buffer, bytes_read);
        }
        fclose(file);
    }

    close(client_socket);
}

int main() {
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    signal(SIGINT, handle_sigint);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Nie można utworzyć gniazda");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Błąd podczas bindowania");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0) {
        perror("Błąd podczas nasłuchiwania");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Serwer nasłuchuje na porcie %d...\n", PORT);

    while (1) {
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("Błąd podczas akceptowania połączenia");
            continue;
        }

        handle_client(client_socket, client_addr);
    }

    close(server_socket);
    return 0;
}
