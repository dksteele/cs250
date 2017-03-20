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
	char cwd[BUFFER_SIZE];
	
	getcwd(cwd, BUFFER_SIZE);
	
	if(argc != 2){
		printf("Usage: %s <server_port>\n", argv[0]);
		return 0;
	}
	
	memset(&addr, '0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[1]));
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Error Creating Socket\n");
		return 0;
	}
	
	int opt_val = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof opt_val);
    
	if(bind(s, (struct sockaddr *) &addr, sizeof(addr)) < 0){
		printf("Error Binding Socket\n");
		return 0;
	}
	
	if(listen(s, 128) < 0){
		printf("Error Listenting\n");
		return 0;
	}
	
	while(1){
		int c;
        if ((c = accept(s, (struct sockaddr *) NULL, NULL)) < 0){ 
			printf("Error Creating Connection\n");
		}
		if(fork() == 0){
			close(s);
			
			char buf[BUFFER_SIZE];
			while (1){				
				
				memset(&buf, '\0', sizeof(buf));
				if(!recv(c, buf, BUFFER_SIZE, 0))
					break;
				
				char path[strlen(buf) + strlen(cwd) + 2];
				memcpy(path, cwd, strlen(cwd));
				path[strlen(cwd)] = '/';
				memcpy(&path[strlen(cwd) + 1], buf, strlen(buf));
				path[strlen(buf) + strlen(cwd) + 1] = '\0';
			
				FILE *file = fopen(path, "r");
				if(file == NULL){
					send(c, "ERROR: File Not Found\n", 22, 0); 
				}else{	
					char line_buf[1024];
					while(fgets(line_buf, 1024, file) != NULL){
						 send(c, line_buf, strlen(line_buf), 0);
					 }
					 fclose(file);
				}
				
				char eof = EOF;
				send(c, &eof, 1, 0);
			}
			close(c);
			exit(0);
		}
		close(c);
	}
	
	return 0;
}
	
