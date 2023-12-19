#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

int count = 0;

void sigint_fun(){
    printf("\a");
    count++;
}

void sigquit_fun(){
    printf("Number of signals sounded: %d", count);
    exit(0);
}

int main(){
    sigset(SIGINT, sigint_fun);
    sigset(SIGQUIT, sigquit_fun);
    while(1);
}