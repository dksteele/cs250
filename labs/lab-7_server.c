#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char* argv[]){
	
	int s;
	struct sockaddr_in addr, cli_addr;
	socklen_t slen=sizeof(cli_addr);
	
	if(argc != 2){
		printf("Usage: %s  <server_port>\n", argv[0]);
		return 0;
	}
	
	memset(&addr, '0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[1]));
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		printf("Error Creating Socket\n");
		return 0;
	}
	
	if(bind(s, (struct sockaddr* ) &addr, sizeof(addr)) < 0){
		printf("Error Binding Socket\n");
		return 0;		
	}
	
	while(1){
		char *in = (char*) malloc(sizeof(char) * INT_MAX);
		int n = recvfrom(s, in, INT_MAX, 0, (struct sockaddr*) &cli_addr, &slen);
		printf("%d\n", n);
	}
	
	close(s);
	
	return 1;
}
	
