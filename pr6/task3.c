#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define PSEVDO_NUM 5  
#define THREADS_AMOUNT 2    
#define N 9               // amount for printing message
#define M 10              // amount of numbers to generate

void *standart_thread(void * params);
void *rand_thread(void * params);

int main() {
    srand(time(0));
    pthread_t threads[THREADS_AMOUNT];
    char * mes = "Work with threads";
    int range = rand() % 15 + 1;

    printf("\nPSEVDO NUMBER: %d\n\n", PSEVDO_NUM);

    pthread_create(&threads[0], NULL, standart_thread, (void *)mes);

    pthread_create(&threads[1], NULL, rand_thread, (void *)&range);

    for (int i = 0; i < THREADS_AMOUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished their work!\n");

    return 0;
}

void *standart_thread(void * params) {
    char * mes = (char *)params;
    for (int i = 1; i <= N; i++) {
        printf("Thread_1. %s Iteration %d\n", mes, i);
        sleep(1);
    }
    pthread_exit(0);
}

void *rand_thread(void * params) {
    int range = *((int *)params);
    for (int i = 1; i <= M; i++) {
        int num = rand() % range;
        printf("Thread_2. Generated num %d\n", num);
        if (num == PSEVDO_NUM) {
            printf("\tThread is stopped!\n");
            pthread_exit(0);
        }
        sleep(1);
    }
    pthread_exit(0);
}