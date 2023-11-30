#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define SHM_SIZE 1024
#define SHM_KEY 2023
#define SEM_KEY 2023

union semnum {
    int val;
    struct semid_ds *buf;
    unsigned short * array;
} sem_arg;

int main() {
    int shm_id, sem_id;
    char *shm_buf;
    int shm_size;
    struct shmid_ds ds;
    struct sembuf sb[1];
    unsigned short sem_vals[1];

    shm_id = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0600);
    if (shm_id == -1) {
        fprintf(stderr, "shmget() error\n");
        return EXIT_FAILURE;
    }

    sem_id = semget(SEM_KEY, 1, 0600 | IPC_CREAT | IPC_EXCL);
    if (sem_id == -1) {
        fprintf(stderr, "semget() error\n");
        return EXIT_FAILURE;
    }
    printf("Semaphore: %d\n", sem_id);
    
    sem_vals[0] = 1;
    sem_arg.array = sem_vals;
    if (semctl(sem_id, 0, SETALL, sem_arg) == -1) {
        fprintf(stderr, "semctl() error\n");
        return EXIT_FAILURE;
    }

    shm_buf = (char *)shmat(shm_id, NULL, 0);
    if (shm_buf == (char *) -1) {
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
            shm_buf[0] = data_count;
            printf("ID: %d\n", shm_id);
            printf("Enter %d data points:\n", data_count);
            for (int i = 1; i <= data_count; ++i) {
                printf("Point %d: ", i);
                scanf("%c", &shm_buf[i]);
            }
            kill(pid_child, SIGUSR1);
            pause();
            printf("Sum calculated (by child process): %c\n", shm_buf[data_count + 1]);
        }
    }

    semctl(sem_id, 1, IPC_RMID, sem_arg);
    shmdt(shm_buf);
    shmctl(shm_id, IPC_RMID, NULL);

    return EXIT_SUCCESS;
}