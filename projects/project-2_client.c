#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char *last_msg;
int sock;

void recieve_signal_handler(int sig_type)
{
	struct sockaddr_in cli_addr;
	char recv_buf[BUFFER_SIZE];
	int num_chars;
	socklen_t slen = sizeof(cli_addr);
	
	if(!(num_chars = recvfrom(sock, recv_buf, BUFFER_SIZE, 0, (struct sockaddr*) &cli_addr, &slen))){
		perror("Recieving");
	}
	recv_buf[num_chars] = '\0';
	printf("%s\n", recv_buf);
}

int main(int argc, char* argv[]){
	
	struct sockaddr_in serv_addr, broad_addr;
	struct hostent *host_ip;

	last_msg = "\0";

	if(argc != 3){
		printf("Usage: %s <server_hostname> <server_port>\n", argv[0]);
		return 0;
	}
	
	signal(SIGIO, recieve_signal_handler);
	
	memset(&broad_addr, '0', sizeof(broad_addr));
	broad_addr.sin_family = AF_INET;
	broad_addr.sin_port = htons(1900);
	broad_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	
	
	if((host_ip = gethostbyname(argv[1])) <= 0){
		perror("Hostname");
		return 0;
	}
	
	serv_addr.sin_addr = *(struct in_addr *) host_ip->h_addr;

	if((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		perror("Creating Recieving Socket\n");
		return 0;
	}
	
	if(bind(sock, (struct sockaddr* ) &broad_addr, sizeof(broad_addr))){
		perror("Binding Socket\n");
		return 0;
	}
	
	int enable_broadcast = 1;
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &enable_broadcast, sizeof(enable_broadcast));
	
	if(fcntl(sock, F_SETOWN, getpid())){
		perror("Setting Socket Owner");
		return 0;
	}
	
	if(fcntl(sock, F_SETFL, O_ASYNC)){
		perror("Setting async and nonblocking");
		return 0;
	}
	
	while(1){
		
		char in[BUFFER_SIZE];
		fgets(in, BUFFER_SIZE, stdin);
		
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
		
		last_msg = malloc(strlen(out));
		strcpy(last_msg, out);
		
		if(!sendto(sock, out, strlen(out), 0, (struct sockaddr*) &serv_addr, sizeof(serv_addr)))
			perror("Sending");
	}
	close(sock);
	
	return 0;
}
