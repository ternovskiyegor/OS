#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int shm_id;
char *shm_ptr;
int sem_id;

void signal_handler(int sig) {
    printf("Client: Signal handler received signal %d\n", sig);
    if (sig == SIGUSR1) {
        int sum = 0, i = 0, val;

        printf("Client: Locking semaphore before reading data...\n");
        struct sembuf op1 = { 0, -1, SEM_UNDO };
        if (semop(sem_id, &op1, 1) == -1) {
            perror("semop P failed");
            exit(EXIT_FAILURE);
        }
        do {
            memcpy(&val, (int *)shm_ptr + i, sizeof(int));
            if (val == 0) break;
            sum += val;
            i++;
        } while (1);

        memcpy(shm_ptr, &sum, sizeof(int));

        printf("Client: Releasing semaphore after reading...\n");
        struct sembuf op2 = { 0, 1, SEM_UNDO };
        if (semop(sem_id, &op2, 1) == -1) {
            fprintf(stderr, "semop error\n");
            exit(EXIT_FAILURE);
        }
        printf("Client: Sending signal back to server...\n");
        kill(getppid(), SIGUSR1);
    }
}

int main(int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <shm_id> <sem_id>\n", argv[0]);
        return 1;
    }

    printf("Client: Connecting to shared memory...\n");
    shm_id = atoi(argv[1]);
    sem_id = atoi(argv[2]);

    shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (void *) -1) {
        fprintf(stderr, "shmat() error\n");
        exit(1);
    }

    printf("Client: Connecting to semaphore...\n");
    signal(SIGUSR1, signal_handler);

    while (1) {
        pause();
    }

    shmdt(shm_ptr);
    return 0;
}