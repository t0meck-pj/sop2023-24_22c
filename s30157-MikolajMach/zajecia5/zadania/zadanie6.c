#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 256
#define FILE_PATH "/tmp/chat_file"

void receive_message() {
    int fd;
    char buffer[BUFFER_SIZE];

    fd = open(FILE_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (read(fd, buffer, BUFFER_SIZE) > 0) {
        printf("Odebrano: %s", buffer);
    }

    close(fd);
}

void send_message(char *message) {
    int fd;

    fd = open(FILE_PATH, O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (write(fd, message, strlen(message)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    close(fd);
}

int main() {
    char message[BUFFER_SIZE];

    while (1) {
        printf("Wpisz wiadomość (q aby wyjść): ");
        fgets(message, BUFFER_SIZE, stdin);

        if (strcmp(message, "q\n") == 0) {
            break;
        }
        send_message(message);
        receive_message();
    }

    return 0;
}

