#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

int main(){
	struct sockaddr_un socket_addresses;
	char buffer[1024];
	int fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(fd < 0){
		perror("The socket was not created!\n");
        return 1;
	}
	memset(&socket_addresses, '0', sizeof(socket_addresses));
	socket_addresses.sun_family = AF_UNIX;
	strncpy(socket_addresses.sun_path, "path", sizeof(socket_addresses.sun_path) - 1);
	if(connect(fd, (struct sockaddr*)&socket_addresses, sizeof(socket_addresses)) == -1){
		perror("The connection was not completed!\n");
        return 1;
	}
	while(1){
		fgets(buffer, 1024, stdin);
		send(fd, buffer, strlen(buffer), 0);
		if(strcmp(buffer, "exit") == 0){
			close(fd);
			return 0;
		}
	}
}