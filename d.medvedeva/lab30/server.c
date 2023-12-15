#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_STR_LENGTH 255

int main() {
    int fds;
    if ((fds = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("Failed to create a socket: ");
        return EXIT_FAILURE;
    }

    struct sockaddr_un address;
    memset(&address, 0, sizeof(address));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, "socket", sizeof(address.sun_path) - 1);

    unlink(address.sun_path);
    if (bind(fds, (struct sockaddr*)&address, sizeof(address)) == -1) {
        perror("Failed to bind a name to the socket: ");
        close(fds);
        return EXIT_FAILURE;
    }

    if (listen(fds, 1) == -1) {
        perror("The socket isn't ready to listen incoming messages: ");
        close(fds);
        return EXIT_FAILURE;
    }

    int c_fds;
    struct sockaddr c_address;
    socklen_t c_address_len = sizeof(c_address);
    if ((c_fds = accept(fds, &c_address, &c_address_len)) == -1) {
        perror("Failed to accept a connection on the socket: ");
        close(fds);
        return EXIT_FAILURE;
    }

    char buffer[MAX_STR_LENGTH];
    ssize_t n;
    while (1) {
        if ((n = read(c_fds, buffer, MAX_STR_LENGTH)) != -1) {
            if (buffer[0] == '\a')
                break;
            for (int i = 0; i < n; ++i)
                printf("%c", toupper(buffer[i]));
        }
        else {
            perror("Failed to read an incoming message: ");
            close(fds);
            return EXIT_FAILURE;
        }
    }

    close(fds);
    return EXIT_SUCCESS;
}
