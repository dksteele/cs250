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
	
	if(argc != 4){
		printf("Usage: %s <server_ip_address> <server_port> <number_of_bytes_to_send>\n", argv[0]);
		return 0;
	}
	
	memset(&addr, '0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	
	if(inet_pton(AF_INET, argv[1], &addr.sin_addr) < 0){
		printf("Error Parsing Ip Address: %s\n", argv[1]);
		return 0;
	}
	
	if((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		printf("Error Creating Socket\n");
		return 0;
	}

	char *out = (char *) malloc(sizeof(char)  * atoi(argv[3]));
	memset(&out[0], '0', atoi(argv[3]));
	sendto(s, out, atoi(argv[3]), 0, (struct sockaddr*) &addr, sizeof(addr));
	perror("sending status : ");
	close(s);
	
	return 1;
}
	
