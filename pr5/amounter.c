#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static int count = 1;

void handler(int signal) {
    printf("Handler %d (signal %d)\n", count, signal);
    sleep(1);
    count++;
}

int main(int argc, char * argv[]) {
    if (argc == 2) {
        // convert string to number (int)
        int num = atoi(argv[1]);
        if (num > 0) {
            for(int i = 1; i <= num; i++) {
                int status = signal(SIGINT, handler);
                if (SIG_ERR == status) {
                    perror("Error signal!\n");
                    return 1;
                }
            }
        } else {
            printf("Error! Amount must be more zer0!\n");
        }
    } else {
        printf("Use: %s <amount>\n", argv[0]);
    }
    return 0;
}
