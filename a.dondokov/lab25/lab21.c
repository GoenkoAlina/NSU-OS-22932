#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int count = 0;

void handleSIGINT() {
    printf("\a");
    fflush(NULL);
    count++;
}

void handleSIGQUIT() {
    printf("\nsignals - %d", count);
    exit(0);
}

int main() {
    signal(SIGINT, &handleSIGINT);
    signal(SIGQUIT, &handleSIGQUIT);

    for(;;);
}