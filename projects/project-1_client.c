#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


#define BUFFER_SIZE 1024
int main(int argc, char* argv[]){
	
	int s;
	struct sockaddr_in addr;
	
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
	
	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Error Creating Socket\n");
		return 0;
	}
	
	if(connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0){
		printf("Unable To Connect\n");
		return 0;
	}
	
	printf("CONNECTED TO %s:%s\n", argv[1], argv[2]);
	
	
	char buf[BUFFER_SIZE];
	while(1){
	
		char *out;
		printf("Enter File Name: ");
		scanf("%m[^\n]%*c", &out);
		
		send(s, out, strlen(out),0);
		
		int last_line = 0;
		
		while(!last_line){
			memset(&buf, '\0', sizeof(buf));
			
			if(!recv(s, buf, BUFFER_SIZE, 0)){
				printf("Server Not Responding\n");
				return 1;
			}
			
			if(buf[strlen(buf) - 1] == EOF){
				buf[strlen(buf) - 1] = '\0'; //Replace EOF with null
				last_line = 1;
			}
			printf("%s", buf);
		}
	}
	
	close(s);
	
	return 0;
}
