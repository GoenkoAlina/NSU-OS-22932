#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
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
    if(connect(fd, (struct sockaddr*)&socket_addresses, sizeof(socket_addresses)) == -1){
        perror("The connection was not completed!\n");
        return 1;
    }
    char* message = "Text for Lab 30!\n";
    if(send(fd, message, strlen(message), 0) == -1){
        perror("The sending was not completed!\n");
        return 1;
    }
    close(fd);
    return 0;
}