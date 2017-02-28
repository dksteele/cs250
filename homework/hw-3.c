#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	
	int s;
	struct sockaddr_in addr;
	socklen_t slen=sizeof(addr);
	
	if(argc != 3){
		printf("Usage: %s <server_ip_address> <server_port>\n", argv[0]);
		return 0;
	}
	
	memset(&addr, '0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	
	if(inet_pton(AF_INET, argv[1], &addr.sin_addr) <= 0){
		printf("Error Parsing Ip Address: %s\n", argv[1]);
		return 0;
	}
	
	if((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		printf("Error Creating Socket\n");
		return 0;
	}
	
	while(1){
	
		char *in, *out;
		printf("Enter Echo Text: ");
		scanf("%m[^\n]%*c", &out);
		
		sendto(s, out, strlen(out), 0, (struct sockaddr*) &addr, sizeof(addr));
		
		in = (char*) malloc(sizeof(char) * strlen(out));
		recvfrom(s, in, strlen(out), 0, (struct sockaddr*) &addr, &slen);
		
		printf("%s\n", in);
	}
	
	close(s);
	
	return 1;
}
	
