#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int signum);

int main() {
    signal(SIGINT, sig_handler);    // Ctrl + C
    signal(SIGTERM, sig_handler);   // kill -15 PID
    signal(SIGUSR1, sig_handler);   // kill -10 PID
    signal(SIGPROF, SIG_DFL);
    signal(SIGHUP, SIG_IGN);

    printf("PID: %d\n", getpid());

    while(1) {
        pause();
    }

    return EXIT_SUCCESS;
}

void sig_handler(int signum) {
    if (signum == SIGINT) {
        printf("\nSIGINT signal\n");
    } else if (signum == SIGTERM) {
        printf("SIGTERM signal\n");
    } else if (signum == SIGUSR1) {
        printf("SIGUSR1 signal. Program stoped!\n");
        exit(EXIT_SUCCESS);
    }
}