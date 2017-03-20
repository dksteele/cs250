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
	
	int s;
	struct sockaddr_in addr;
	struct hostent *host_ip;
	
	if(argc != 3){
		printf("Usage: %s <server_hostname> <server_port>\n", argv[0]);
		return 0;
	}
	
	memset(&addr, '0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	
	
	
	if((host_ip = gethostbyname(argv[1])) <= 0){
		printf("Hostname Error: %s\n", argv[1]);
		return 0;
	}
	
	addr.sin_addr = *(struct in_addr *) host_ip->h_addr;
	
	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Error Creating Socket\n");
		return 0;
	}

	struct timeval to;
	to.tv_sec = 10;
	to.tv_usec = 0;
	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof(to));
	
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
			
<<<<<<< HEAD
			if(!recv(s, buf, BUFFER_SIZE, 0)){
				printf("Server Not Responding\n");
				return 1;
			}
			
			if(buf[strlen(buf) - 1] == EOF){
=======
			int ret = recv(s, buf, BUFFER_SIZE, 0);
			if(!ret || buf[strlen(buf) - 1] == EOF){
>>>>>>> 0346e3e8eca47f0f621aac9172abdec8f2712c19
				buf[strlen(buf) - 1] = '\0'; //Replace EOF with null
				last_line = 1;
			}
			printf("%s", buf);
		}
	}
	
	close(s);
	
	return 0;
}
