#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int main() {
    char buffer[BUFFER_SIZE];
    int fd;

    fd = open("tmp/chat", O_WRONLY | O_CREAT | O_APPEND, 0666);

    while (1) {
        printf("Wpisz swoją wiadomość (wpisz EXIT, aby wyjść):\n");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "EXIT") == 0)
            break;

        write(fd, buffer, strlen(buffer));
        write(fd, "\n", 1);
    }

    close(fd);

    return 0;
}
