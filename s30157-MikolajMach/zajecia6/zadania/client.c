#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void download_file(int socket, char *filename) {
    int filename_length = htonl(strlen(filename));
    write(socket, &filename_length, sizeof(filename_length));
    write(socket, filename, strlen(filename));

    int file_size;
    read(socket, &file_size, sizeof(file_size));
    file_size = ntohl(file_size);

    if (file_size == -1) {
        printf("Nie można otworzyć pliku: %s\n", filename);
        return;
    }

    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Nie można utworzyć pliku");
        return;
    }

    char buffer[BUFFER_SIZE];
    int bytes_received;
    while ((bytes_received = read(socket, buffer, BUFFER_SIZE)) > 0) {
        fwrite(buffer, 1, bytes_received, file);
    }

    fclose(file);
    printf("Plik %s został pobrany pomyślnie.\n", filename);
}

int main() {
    struct sockaddr_in server_addr;
    char filename[BUFFER_SIZE];

    printf("Podaj nazwę pliku do pobrania: ");
    scanf("%s", filename);

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Nie można utworzyć gniazda");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Nie można połączyć się z serwerem");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    download_file(client_socket, filename);

    close(client_socket);
    return 0;
}
