#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]){
	int s;
	struct sockaddr_in addr, cli_addr;
	socklen_t slen=sizeof(cli_addr);
	
	const char *reg = "";
	regex_t regex;
	if(regcomp(&regex, "[A-Za-z]*[[:space:]][A-Za-z]*[[:space:]][0-9]*[[:space:]]([0-9]*:[0-9]*:[0-9]*)[[:space:]][A-Za-z]*[[:space:]][0-9]*", REG_EXTENDED)){
		printf("Could Not Compile Regex");
		return 0;
	}
	
	memset(&addr, '0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1337);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		printf("Error Creating Socket\n");
		return 0;
	}
    
	if(bind(s, (struct sockaddr *) &addr, sizeof(addr)) < 0){
		printf("Error Binding Socket\n");
		return 0;
	}

	char buf[BUFFER_SIZE];
	while(1){
		if (recvfrom(s, buf, BUFFER_SIZE, 0, (struct sockaddr*)&cli_addr, &slen)==-1){
			printf("Error Recieving");
			continue;
		}

		FILE *cmd_out = popen("date\0", "r");
		if(cmd_out == NULL)
			return 0;
		
		char line_buf[1024];
		while(fgets(line_buf, 1024, cmd_out) != NULL)
			continue;
		
		
		pclose(cmd_out);
		
		regmatch_t matches[2];
		int ret = regexec(&regex, line_buf, 2, matches, 0);
		if(ret){
			printf("REGEX Failed");
			continue;
		}
		
		char time[8];
		memcpy(time, &line_buf[matches[1].rm_so], matches[1].rm_eo - matches[1].rm_so);
		
		sendto(s, time, 8, 0, (struct sockaddr*) &cli_addr, sizeof(cli_addr));
	}
	
	return 1;
}
	
