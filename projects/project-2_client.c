#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


#define BUFFER_SIZE 1024
int main(int argc, char* argv[]){
	
	int recv_sock, send_sock;
	struct sockaddr_in serv_addr;
	struct hostent *host_ip;
	char recv_buf[BUFFER_SIZE];
	
	if(argc != 3){
		printf("Usage: %s <server_hostname> <server_port>\n", argv[0]);
		return 0;
	}
	
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	
	
	if((host_ip = gethostbyname(argv[1])) <= 0){
		perror("Hostname");
		return 0;
	}
	
	serv_addr.sin_addr = *(struct in_addr *) host_ip->h_addr;
	
	if((send_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		perror("Creating Sending Socket\n");
		return 0;
	}
	
	if((recv_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		perror("Creating Recieving Socket\n");
		return 0;
	}
	
	if(fork() == 0){
		close(recv_sock);
		
		while(1){
			
			char *in;
			scanf("%m[^\n]%*c", &in);
			
			time_t tm = time(NULL);
			char *str_time = ctime(&tm);
			str_time[strlen(str_time) - 1] = '\0'; //Remove new line and null terminate string
			
			char *user = getenv("USER");
			
			
			char *out = malloc(strlen(in) + strlen(str_time) + strlen(user) + 7);
			strcpy(out, str_time);
			strcat(out, " [");
			strcat(out, user);
			strcat(out, "] : ");
			strcat(out, in);
			strcat(out, "\0"); //Null terminate string
			
			if(!sendto(send_sock, out, strlen(out), 0, (struct sockaddr*) &serv_addr, sizeof(serv_addr)))
				perror("Sending");
		}
		close(send_sock);
	}else{
		close(send_sock);
		
		while(1){
			if(recv(recv_sock, recv_buf, BUFFER_SIZE, 0)){
				recv_buf[strlen(recv_buf) - 1] = '\0';
				printf("%s", recv_buf);
			}
		}
		
		close(recv_sock);
	}
	
	return 0;
}
