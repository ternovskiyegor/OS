#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define SHM_SIZE 1024

int main(int argc, char ** argv) {
    int shm_id;
    int * shm_data;
    int shm_size;

    shm_id = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0600);
    if (shm_id == -1) {
        fprintf(stderr, "shmget() error\n");
        return EXIT_FAILURE;
    }

    shm_data = (int*) shmat(shm_id, NULL, 0);
    if (shm_data == (int *) -1) {
        fprintf(stderr, "shmat() error\n");
        return EXIT_FAILURE;
    }

    pid_t pid_child = fork();

    if (pid_child < 0) {
        fprintf(stderr, "fork() error\n");
        return EXIT_FAILURE;
    } else if (pid_child == 0) {
        execl("./child", "child", NULL);
    } else {
        while (1) {
            int data_count;
            printf("Enter the number of data points (or type 'q' to quit):\n");
            char input[50];
            fgets(input, sizeof(input), stdin);
            if (strcmp(input, "q\n") == 0 || strcmp(input, "quit\n") == 0) {
                kill(pid_child, SIGTERM);
                break;
            }
            data_count = atoi(input);
            shm_data[0] = data_count;
            printf("ID: %d\n", shm_id);
            printf("Enter %d data points:\n", data_count);
            for (int i = 1; i <= data_count; ++i) {
                printf("Point %d: ", i);
                scanf("%d", &shm_data[i]);
            }
            kill(pid_child, SIGUSR1);
            pause();
            printf("Sum calculated (by child process): %d\n", shm_data[data_count + 1]);
        }
    }

    shmdt(shm_data);
    shmctl(shm_id, IPC_RMID, NULL);

    return EXIT_SUCCESS;
}