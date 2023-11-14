#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 4 // Amount of threads
#define M 3 // Amount of repeats

struct thread_params {
    char * name;  // name of thread
    char * str;   // string for printing
    int num;      // amount of repeats
};

void *thread_func(struct thread_params *params);

int main() {
    // array of the threads
    pthread_t threads_array[N];
    // array of the params 
    struct thread_params params[N] = {
        {"A", "One", 2},
        {"B", "Two", 3},
        {"C", "Three", 4},
        {"D", "Four", 4}
    };

    for (int i = 0; i < N; i++) {
        if (pthread_create(&threads_array[i], NULL, (void*)thread_func, &params[i]) != 0) {
            perror("Error in creating thread!\n");
            return 1;
        }
        if (pthread_join(threads_array[i], NULL) != 0) {
            perror("Error joinind thread!\n");
        }
    }

    // run without waiting thread
    
    // for (int i = 0; i < N; i++) {
    //     if (pthread_join(threads_array[i], NULL) != 0) {
    //         perror("Error joinind thread!\n");
    //     }
    // }
    
    return 0;
}

void *thread_func(struct thread_params *params) {
    for (int i = 1; i <= params->num; i++) {
        printf("Thread %s. %s, Repeats: %d/%d\n", params->name, params->str, i, params->num);
        sleep(1);
    }
    pthread_exit(0);
}