#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigaction_handler(int signum);

int main() {
    struct sigaction sa;

    sa.sa_handler = sigaction_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);
    signal(SIGPROF, SIG_DFL);
    signal(SIGHUP, SIG_IGN);

    printf("PID: %d\n", getpid());

    while (1) {
        pause();
    }

    return EXIT_SUCCESS;
}

void sigaction_handler(int signum) {
    if (signum == SIGINT) {
        printf("\nSIGINT signal\n");
    } else if (signum == SIGTERM) {
        printf("SIGTERM signal\n");
    } else if (signum == SIGUSR1) {
        printf("SIGUSR1 signal. Program stoped!\n");
        exit(EXIT_SUCCESS);
    }
}