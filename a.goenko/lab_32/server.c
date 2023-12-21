#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/un.h>

int main(){
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(fd == -1){
        perror("The socket was not created!\n");
        return 1;
    }
    struct sockaddr_un socket_addresses;
    memset(&socket_addresses, 0, sizeof(socket_addresses));
    socket_addresses.sun_family = AF_UNIX;
    char path[100] = "path";
    strncpy(socket_addresses.sun_path, path, strlen(path));
    unlink(socket_addresses.sun_path);
    if(bind(fd, (struct sockaddr*)&socket_addresses, sizeof(socket_addresses)) == -1){
        perror("The binding to the socket was not completed!\n");
        return 1;
    }
    if(listen(fd, 1) == -1){
        perror("The listening was not completed");
        return 1;
    }
    int fd_, n;
    struct sockaddr_un socket_addresses_;
    socklen_t size_ = sizeof(socket_addresses_);
	char buffer[1024];
	pid_t childpid;
	while(1){
		if((fd_ = accept(fd, (struct sockaddr*)&socket_addresses_, &size_)) == -1){
			perror("The accepting was not fulfilled!\n");
			return 1;
    	}
		if((childpid = fork()) == 0){
			close(fd);
			while(1){
				n = read(fd_, buffer, 1024);
				if(strcmp(buffer, ":exit") == 0){
					break;
				}else{
                    int j = 0;
                    while (j<n){
					    printf("%c", toupper(buffer[j]));
                        j++;
                    }
				}
			}
		}

	}
	close(fd_);
	return 0;
}