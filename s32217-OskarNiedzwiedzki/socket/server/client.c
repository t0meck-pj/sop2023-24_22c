#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFFER_LENGTH 256
typedef unsigned char BYTE;

void error(char* msg){
	perror(msg);
	exit(1);
}

int main(int argc, char** argv){
	int sockfd, port, n;
	struct sockaddr_in serv_addr;
	struct hostent* server;

	int filename_len=0;
	int read_len=0;
	int bytes_read=0;
	BYTE buffer[BUFFER_LENGTH];
	FILE* f;

	if(argc < 5){
		printf("hostname [argument1], port [argument2], filename[argument3] and out_filename_path[argument4] must be provided!");
		exit(1);
	}

	port = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) error("ERROR opening socket");

	server = gethostbyname(argv[1]);
	if(server==NULL) error("Host does not exist, or is unable to connect");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	memcpy(&serv_addr.sin_addr.s_addr,server->h_addr_list[0], server->h_length);
	serv_addr.sin_port = htons(port);

	if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR connecting to the server");


	/*send filename length*/
	filename_len = strlen(argv[3]);
	n = write(sockfd,&filename_len, sizeof(int)); 
	if(n<0) error("ERROR writing to socket -> filename_length could not be written");

	n = write(sockfd, argv[3], filename_len+1); /*+1 for termination character*/
	if(n<0) error("ERROR writing to socket -> filename could not be written");

	memset(buffer,0,BUFFER_LENGTH);
	n = read(sockfd, &read_len, sizeof(int)); /*get readed file length*/
	if(n<0) error("ERROR reading from socket -> out file length could not be read");
	else if(read_len < 0){
		printf("File cannot be downloaded (does not exists or is corrupted)\n");
		return EXIT_SUCCESS;
	}

	f = fopen(argv[4], "wb");
	if(f==NULL){
		fprintf(stderr, "out file (argument 4) could not be created\n");
		close(sockfd);
		return EXIT_FAILURE;
	}

	while(bytes_read<read_len){
		n = read(sockfd,buffer,BUFFER_LENGTH);
		if(n<0) error("ERROR reading from socket -> file is corrupted!");
		fwrite(buffer,sizeof(BYTE),n,f);
		bytes_read+=n;
	}

	printf("File has been downloaded\n");
	fclose(f);
	return 0;
}
