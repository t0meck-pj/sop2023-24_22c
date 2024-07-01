#define HTTP_SERVER
#define TRUE 1>0
#define FALSE 1<0

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <regex.h>
#include <time.h>
#include "memory_manager.h"

#define MAX_CONNECTIONS 16
#define BUFFER_LENGTH 256
#define HTTP_BUFFER 4096 /*average size of request is around 800 bytes (google.com request)*/
const char* log_file_path="/tmp/s32217_serverlog.log";
const char* blacklist_file_path="/tmp/s32217_serverblacklist";

typedef unsigned char BYTE;

/*global variables*/
FILE* log_file=NULL;
char log_buffer[BUFFER_LENGTH]; /*buffer for logging messages*/
pid_t main_process; /*main process pid_t*/
int port, clilen;
int sockfd, newsockfd; /*parent socket, and child sockets*/
struct sockaddr_in serv_addr, cli_addr;
/*END global variables*/

void log_error(char* msg, FILE*);/*logs error and terminates program*/
void log_info(char*, FILE*); /*logs informations, does not terminate program*/

int check_blacklist(struct in_addr*); /*returns o > 0 if user is permitted, or o == 0 if user is on the address blacklist*/

void service_send_file(int);
void service_http_request(int);

int http_send_header(int,const char*); /*sends proper http header to socket, returns http_code*/
void http_send_file(int, const char*);

char* url_decode(const char*);
char* get_file_extension(const char*);
const char* get_mime_type(const char*);

void ctrlc_handler(int);
void server_setup(int, char**);

int main(int argc, char** argv){
	pid_t child; /*child proces id*/	

	if(argc < 2){
		fprintf(stderr,"ERROR, port has not been provided\n");
		return EXIT_FAILURE;
	}

	mem_manager_init();
	server_setup(argc, argv);

	/*listen to new connections*/
	while(1){
		newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, (unsigned int* __restrict__) &clilen);
		if(newsockfd < 0) log_error("accept", log_file);

		child = fork();
		if(child<0) log_error("fork", log_file);
		else if(child==0){
			close(sockfd);
			sprintf(log_buffer,"Connected with user: (%s)",inet_ntoa(cli_addr.sin_addr));
			log_info(log_buffer, log_file);

			if(!check_blacklist(&cli_addr.sin_addr)){
				sprintf(log_buffer,"User (%s) is on the user blacklist, access denied",inet_ntoa(cli_addr.sin_addr));
				log_error(log_buffer, log_file);	
			}	
#ifdef HTTP_SERVER
			service_http_request(newsockfd);
			sprintf(log_buffer,"HTTP: disconnecting, with user: (%s)", inet_ntoa(cli_addr.sin_addr));
			log_info(log_buffer, log_file);
#else
			service_send_file(newsockfd);
			sprintf(log_buffer, "File has been/has not been sent, disconnecting with user: (%s)", inet_ntoa(cli_addr.sin_addr));
#endif
			sprintf(log_buffer, "Memory usage after request: %ld bytes of memory used. Number of memory blocks reserved: %d", 
								mem_manager.allocated_bytes, 
								mem_manager.block_refs->get_size(mem_manager.block_refs));
			log_info(log_buffer, log_file);
			close(newsockfd);
			exit(EXIT_SUCCESS);
		}
		else close(newsockfd);
	}
}

void log_error(char* msg, FILE* log){
	char date_str[64];
	time_t rawtime;
	struct tm* timeinfo; /*localtime is points to the static region of memory, do not use free on it*/

	if(log==NULL) return;

	time(&rawtime);
	timeinfo=localtime(&rawtime);
	strftime(date_str, sizeof(date_str),"%d-%m-%Y %H:%M:%S",timeinfo);

	fprintf(log, "(%s)[Error] %s\n",date_str, msg);
	exit(EXIT_FAILURE);
}

void log_info(char* msg, FILE* log){
	char date_str[64];
	time_t rawtime;
	struct tm* timeinfo;
	
	if(log==NULL)return;

	time(&rawtime);
	timeinfo=localtime(&rawtime);
	strftime(date_str, sizeof(date_str), "%d-%m-%Y %H:%M:%S", timeinfo);

	fprintf(log, "(%s)[Info] %s\n",date_str, msg);
	fflush(log);/*flush the stream at the end, to save to the file*/
}

int check_blacklist(struct in_addr* sin_addr_ref){
	char line[32];
	FILE* blacklist = fopen(blacklist_file_path, "r");

	/*1>0 -> TRUE 0>1 -> FALSE*/
	/*if blacklist file does not exist, return 1 meaning that user is not on the blacklist*/
	if(blacklist==NULL) return 1>0;
	while(!feof(blacklist)){
		fgets(line, sizeof(line), blacklist);
		line[strlen(line)-1]='\0'; /*fgets returns string with newline, which we do not want to have, this removes it*/
		if(strcmp(inet_ntoa(*sin_addr_ref), line)==0){
			fclose(blacklist);
			return FALSE; /*user is on the blacklist*/
		}
	}

	fclose(blacklist);
	return TRUE;
}

void ctrlc_handler(int signum){

	if(getpid()!=main_process){
		sprintf(log_buffer,"Thread has been force quit. Download may have been interrupted. Thread id: (%d)", getpid());
		log_error(log_buffer, log_file);
		close(newsockfd);
		exit(EXIT_FAILURE);
	}
	else{
		kill(0,SIGINT); /*kill all child processes, 0 from posix specs means that all child processes in given group will be sent this signal*/
		while(wait(NULL)>0); /*wait for all children to end their job*/
		printf("Server has been disabled\n");
		log_info("Server has been force quit", log_file);
		close(sockfd);
		exit(EXIT_SUCCESS);
	}
}

void service_send_file(int socket){
	int buffer[BUFFER_LENGTH];
	int n=0;
	int filename_len=0;
	char* filename=NULL;
	FILE* file=NULL;
	long send_length=0;
	int bytes_read=0;
	BYTE send_buffer[BUFFER_LENGTH]; /*file will be sent in 256 bytes chunks*/

	memset(buffer,0,sizeof(buffer));
	if((n=read(socket, &filename_len, sizeof(int))) < 0) log_error("server read filename_len", log_file);
	filename = allocate(sizeof(char), filename_len+1);
	if((n=read(socket,filename, filename_len))<0) log_error("server read filename", log_file);

	sprintf(log_buffer, "User requested file: %s", filename);
	log_info(log_buffer, log_file);

	file = fopen(filename, "rb");
	if(file==NULL){
		log_info("Requested file does not exist", log_file);
		send_length=-1;
		n = write(socket, &send_length, sizeof(int));
		if(n<0) log_error("server write send_length", log_file);
		exit(0);
	}

	/*get file length*/
	fseek(file,0,SEEK_END);
	send_length = ftell(file);
	rewind(file);
	if((n=write(socket, &send_length,sizeof(send_length))) < 0) log_error("server write send_length", log_file);

	sprintf(log_buffer, "Preparing to send %ld bytes in %d bytes packets", send_length, BUFFER_LENGTH);
	log_info(log_buffer, log_file);

	while(!feof(file)){
		memset(send_buffer,0,sizeof(send_buffer));
		bytes_read=fread(send_buffer, BUFFER_LENGTH,sizeof(BYTE),file);
		if((n=write(socket,send_buffer,bytes_read))<0) log_error("server write send_buffer", log_file);
	}

	sprintf(log_buffer, "Successfully send %s, size(%ld)", filename, send_length);
	log_info(log_buffer,log_file);

	fclose(file);
	destroy(filename);
}

char* url_decode(const char* url){
	int len = strlen(url);
	char* decoded = allocate(sizeof(char), len+1);
	int decoded_iter=0;
	unsigned int hex_val=0;
	int i=0;

	for(i=0;i<len;i++){
		if(url[i]=='%' && i + 2 < len){
			sscanf(url+i+1,"%2x", &hex_val);
			decoded[decoded_iter++] = hex_val;
			i+=2;	
		}
		else
			decoded[decoded_iter++] = url[i];
	}

	/*add terminator*/
	decoded[decoded_iter]='\0';
	return decoded;

}

char* get_file_extension(const char* filename){
	char* dot = strrchr(filename, '.'); /*find dot in string*/
	if(dot==NULL || dot==filename) /*dot has not been found, or points to the beginning of the filename string*/
		return "";
	return dot+1; /*return everything after dot*/
}

const char* get_mime_type(const char* file_extension){
	if(strcmp(file_extension,"html")==0 || strcmp(file_extension,"htm")==0)
		return "text/html";
	else if(strcmp(file_extension,"txt")==0)
		return "text/plain";
	else if(strcmp(file_extension,"jpg")==0 || strcmp(file_extension,"jpeg")==0)
		return "image/jpeg";
	else if(strcmp(file_extension,"png")==0)
		return "image/png";
	else
		return "application/octet-stream";
}

int http_send_header(int socket, const char* filename){
	const char* file_ext = NULL;
	const char* mime_type = NULL;
	int n=0;
	int http_code=0;
	FILE* f=NULL;
	char header[HTTP_BUFFER];

	file_ext = get_file_extension(filename);
	mime_type = get_mime_type(file_ext);

	f=fopen(filename,"r");

	if(f==NULL){ /*if file has not been found, send 404 not found*/
		sprintf(header,
				"HTTP/1.1 404 Not Found\r\n"
				"Content-Type: text/plain\r\n"
				"\r\n");
		http_code=404;
	}
	else{
		sprintf(header, "HTTP/1.1 200 OK\r\n"
				"Content-Type: %s\r\n"
				"\r\n",
				mime_type);
		http_code = 200;
	}

	n = write(socket, header, strlen(header));
	if(n<0) log_error("HTTP send request write error", log_file);

	fclose(f);
	return http_code;
}

void http_send_file(int socket, const char* filename){
	FILE* f = fopen(filename, "rb");
	BYTE send_buffer[BUFFER_LENGTH];
	int bytes_read=0;
	int n=0;

	if(f==NULL) log_error("HTTP send, requested file does not exist", log_file);

	while(!feof(f)){
		memset(send_buffer,0,sizeof(send_buffer));
		bytes_read=fread(send_buffer, sizeof(BYTE), BUFFER_LENGTH,f);
		n = write(socket, send_buffer, bytes_read);
		if(n<0) log_error("HTTP send_file, error while sending file", log_file);
	}

	fclose(f);
}

void service_http_request(int socket){
	int n=0;
	int http_code=0;
	char request[HTTP_BUFFER];
	char filename_encoded[BUFFER_LENGTH];
	char* filename_decoded=NULL; /*dynamically allocated memory, use free to free memory*/
	int match_length=0;
	regex_t regex;
	regmatch_t matches[2];

	n = read(socket, request, sizeof(request));
	if(n<0) log_error("HTTP request read", log_file);

	regcomp(&regex, "^GET ([^ ]*) HTTP/1", REG_EXTENDED); /*compile regex, this regex gets filepath from get request*/

	if(regexec(&regex, request, 2, matches,0)!=0)
		log_error("HTTP regex error", log_file);


	match_length = matches[1].rm_eo - matches[1].rm_so;
	memset(filename_encoded,0,BUFFER_LENGTH); /*zero memory, to prevent from errors i have been looking for error here for almost 5 hours*/
	strncpy(filename_encoded, request + matches[1].rm_so, match_length);
	filename_decoded=url_decode(filename_encoded);

	sprintf(log_buffer,"sending request: %s (type: %s)", filename_decoded, get_mime_type(filename_decoded));
	log_info(log_buffer, log_file);

	http_code=http_send_header(socket, filename_decoded);

	if(http_code==404){
		n = write(socket,"404 Not Found", strlen("404 Not Found") +1);
		if(n<0) log_error("HTTP 404 write error", log_file);
	}
	else if(http_code==200)
		http_send_file(socket, filename_decoded);

	sprintf(log_buffer, "Request sent successfully with code %d", http_code);
	log_info(log_buffer, log_file);

	destroy(filename_decoded);
}

void server_setup(int argc, char** argv){
	struct sigaction ctrlc;

	main_process = getpid(); /*get main process id*/
	ctrlc.sa_handler = ctrlc_handler;
	sigaction(SIGINT,&ctrlc,NULL);

	/*create log file*/
	log_file = fopen(log_file_path, "a");
	if(log_file==NULL){
		fprintf(stderr, "Log file could not be created\n");
		exit(EXIT_FAILURE);
	}

	sockfd = socket(AF_INET, SOCK_STREAM,0); /*create socket*/

	if(sockfd < 0)	log_error("socket could not be opened", log_file);
	memset(&serv_addr, 0, sizeof(serv_addr)); /*zero the memory*/

	port = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
	if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
		log_error("binding was unsucessfull",log_file);

	listen(sockfd, MAX_CONNECTIONS); /*start listening to the socket, max 16 connection can be queued*/
	clilen = sizeof(cli_addr);
}

