#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10  // AMOUNT OF SIMPLE AND CATALAN FIRST NUMS

void * find_catalan();
void * find_simple();
int is_num_simple(int num);
void print_arr(int * arr);
unsigned long long factorial(unsigned int n);

int main() {
    pthread_t simple_thread;
    pthread_t catalan_thread;

    void * catalan_result;
    void * simple_result;

    pthread_create(&simple_thread, NULL, find_simple, NULL);
    pthread_create(&catalan_thread, NULL, find_catalan, NULL);

    pthread_join(simple_thread, &simple_result);
    pthread_join(catalan_thread, &catalan_result);

    int * simple_nums = (int *)simple_result;
    printf("Simple nums:\n");
    print_arr(&simple_nums[0]);
    int * catalan_nums = (int *)catalan_result;
    printf("Catalan nums:\n");
    print_arr(&catalan_nums[0]);

    return 0;
}

void * find_catalan() {
    int *arr = (int *)malloc(N * sizeof(int));
    arr[0] = 1;
    for (int i = 1; i < N; i++) {
        int num = factorial(2 * i)/(factorial(i + 1) * factorial(i));
        arr[i] = num;
    }
    pthread_exit((void *)arr);
}

void * find_simple() {
    unsigned long long *arr = (unsigned long long *)malloc(N * sizeof(unsigned long long));
    int counter = 0;
    unsigned long long num = 2;
    while (counter < N) {
        if (is_num_simple(num)) {
            arr[counter] = num;
            counter++;
        }
        num++;
    }
    pthread_exit((void *)arr);
}

int is_num_simple(int num) {
    for (int i = 2; i * i <= num;  i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

unsigned long long factorial(unsigned n) {
    return (n < 2) ? 1 : n * factorial(n - 1);
}

void print_arr(int * arr) {
    printf("[");
    for (int i = 0; i < N; i++) {
        printf(" %d", arr[i]);
    }
    printf(" ]\n");
}