/*Create simple chat app. It uses file in /tmp folder as chat.
We check if file exists, if not we create it. 
Then, we prints all messages from file and waits for new messages.
When we write message, we append it to file using child process (so two instances of a program should be able to write to file at the same time).
After writing message, we print file again and wait for new messages.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void readMessages(int file){
    char buffer[256];
    int bytesRead;
    lseek(file, 0, SEEK_SET);
    while((bytesRead = read(file, buffer, sizeof(buffer))) > 0){
        write(1, buffer, bytesRead);
    }
}

int main(){
    int file;
    char buffer[256];
    int bytesRead;
    pid_t pid;

    file = open("/tmp/chat", O_CREAT | O_RDWR, 0666);
    if(file == -1){
        printf("File already exists\n");
        exit(1);
    }

    while(1){
        readMessages(file);
        printf("Enter message: ");
        fgets(buffer, sizeof(buffer), stdin);
        pid = fork();
        if(pid == 0){
            write(file, buffer, strlen(buffer));
            exit(0);
        }
        else{
            wait(NULL);
        }
    }

    return 0;
}

