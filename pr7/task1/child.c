#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main(int argc, char ** argv) {
    int shm_id;
    int * shm_data;

    if (argc < 2) {
        fprintf(stderr, "Too few arguments\n");
        exit(EXIT_FAILURE);
    }

    shm_id = atoi(argv[1]);
    
    shm_data = (int *) shmat(shm_id, 0, 0);
    if (shm_data == (int *) -1) {
        fprintf(stderr, "shmat() error\n");
        return EXIT_FAILURE;
    }

    while (1) {
        while (!shm_data[0]);
        int sum = 0;
        int data_count = shm_data[0];
        for (int i = 1; i <= data_count; ++i) {
            sum += shm_data[i];
        }
        shm_data[data_count + 1] = sum;
        shm_data[0] = 0;
        kill(getppid(), SIGUSR1);
    }

    shmdt(shm_data);

    return EXIT_SUCCESS;
}
