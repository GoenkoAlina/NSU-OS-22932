#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid == -1) { return 1; }

    if (pid == 0) { execlp("cat", "cat", "../main.c", NULL); return 1;} 
    else {
        if(wait(NULL) != -1) {
            printf("\nChild process (pid: %d) finished\n", pid);
        }
    }

    return 0;
}