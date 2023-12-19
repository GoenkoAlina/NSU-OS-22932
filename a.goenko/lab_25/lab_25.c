#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <string.h>

int main(){
    int fd[2];
    if(pipe(fd) == -1){
        perror("The pipeline was not created!\n");
        return 1;
    }
    pid_t subprocess = fork();
    if(subprocess == -1){
        perror("The subprocess was not created!\n");
        return 1;
    }
    else if(subprocess == 0){
        close(fd[1]);
        char buf;
        while(read(fd[0], &buf, sizeof(char))){
            printf("%c", toupper(buf));
        }
        close(fd[0]);
    }
    else{
        close(fd[0]);
        char* message = "Text for Lab 25\n!";
        write(fd[1], message, strlen(message));
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}