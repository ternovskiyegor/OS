#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void handler(int sig) {
    printf("Time to go...\n");
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Use: %s <time in seconds> <message>\n", argv[0]);
        return 1;
    }

    int time = atoi(argv[1]);
    if (time <= 0) {
        fprintf(stderr, "Invalid time value!\n");
        return 1;
    }
    char *message = argv[2];

    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork() error!\n");
        exit(1);
    } else if (pid == 0) {
        // child
        signal(SIGALRM, handler);
        alarm(time); // generate a SIGALRM signal
        pause();
        printf("Alarm signal: %s\n", message);
        exit(0);
    } else {
        // parent
        printf("Alarm set on %d seconds. PID: %d\n", time, pid);
        exit(0);
    }
    return 0;
}