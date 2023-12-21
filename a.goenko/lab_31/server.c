#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <ctype.h>
#include <sys/select.h>
#include <sys/un.h>


int main(){
	struct sockaddr_un socket_addresses;
	char buffer[1024];
	int fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(fd == -1){
		perror("The socket was not created!\n");
        return 1;
	}
	memset(&socket_addresses, '\0', sizeof(socket_addresses));
	socket_addresses.sun_family = AF_UNIX;
    char path[100] = "path";
    strncpy(socket_addresses.sun_path, path, sizeof(socket_addresses.sun_path) - 1);
    unlink(socket_addresses.sun_path);
	if(bind(fd, (struct sockaddr*)&socket_addresses, sizeof(socket_addresses)) == -1){
		perror("The binding to the socket was not completed!\n");
        return 1;
	}
	if(listen(fd, 100) == -1){
		perror("The listening was not completed");
        return 1;
	}
    int n;
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    FD_SET(fd, &rfds);
    int mfd = fd;
    fd_set r;
    while (1) {
        r = rfds;
        if (select(mfd + 1, &r, NULL, NULL, NULL) == -1) {
            perror("Select was not completed");
            close(fd);
            return 1;
        }
        if (FD_ISSET(fd, &r)) {
            int c_fds;
            struct sockaddr addr;
            socklen_t addr_len = sizeof(addr);
            if ((c_fds = accept(fd, &addr, &addr_len)) == -1) {
                perror("The accepting was not fulfilled!\n");
                close(fd);
                return 1;
            }
            FD_SET(c_fds, &rfds);
            if (c_fds > mfd)
                mfd = c_fds;
        }
        if (FD_ISSET(0, &r))
            break;
        int i = 0;
        for (i; i <= mfd; i++) {
            if (FD_ISSET(i, &r)) {
                if (i == fd)
                    continue;
                n = read(i, buffer, 1024);
                if (*buffer == '\a') {
                    FD_CLR(i, &rfds);
                    continue;
                }
                int j = 0;
                for (j; j < n; j++)
                    printf("%c", toupper(buffer[j]));
            }
        }
    }
	close(fd);
	return 0;
}