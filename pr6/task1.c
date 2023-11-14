#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
#define SLEEP_TIME 1

void * thread_func();

int main() {
    pthread_t my_thread;
    
    for (int i = 1; i <= N; i++) {
        printf("Main Thread. Iteration %d\n", i);
        if (pthread_create(&my_thread, NULL, thread_func, NULL) != 0) {
            perror("Error in creating thread!\n");
            return 1;
        }
        if (pthread_join(my_thread, NULL) != 0) {
            perror("Error joining thread!\n");
            return 1;
        }
        sleep(SLEEP_TIME);
    }
    return 0;
}

void * thread_func() {
    for (int i = 1; i <= N; i++) {
        printf("Child thread. Iteration %d\n", i);
        sleep(SLEEP_TIME);
    }
    pthread_exit(0);
}