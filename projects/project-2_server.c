#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


#define BUFFER_SIZE 1024
int main(int argc, char* argv[]){
	
	int sock;
	struct sockaddr_in serv_addr, broad_addr, cli_addr;
	socklen_t slen = sizeof(cli_addr);
	char recv_buf[BUFFER_SIZE];
	
	if(argc != 2){
		printf("Usage: %s <server_port>\n", argv[0]);
		return 0;
	}
	
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	memset(&broad_addr, '0', sizeof(broad_addr));
	broad_addr.sin_family = AF_INET;
	broad_addr.sin_port = htons(1900);
	broad_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	
	if((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		perror("Creating Socket\n");
		return 0;
	}

	if(bind(sock, (struct sockaddr* ) &serv_addr, sizeof(serv_addr))){
		perror("Binding Socket\n");
		return 0;
	}
	
	int enable_broadcast = 1;
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &enable_broadcast, sizeof(enable_broadcast));
	
	while(1){
		int num_chars = 0;
		if((num_chars = recvfrom(sock, recv_buf, BUFFER_SIZE, 0, (struct sockaddr*) &cli_addr, &slen))){
			recv_buf[num_chars] = '\0';
			if(sendto(sock, recv_buf, strlen(recv_buf), 0, (struct sockaddr *) &broad_addr, sizeof(broad_addr)))
				printf("Relayed");
			else
				perror("Send");
			
		}else{
			perror("Recieve");
		}
	}
	
	
	close(sock);

	return 0;
}
