#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// generate array on N - elements
void generateArray(int * arr, int size);
// find average num of the array
float findAverage(int * arr, int size);
// find nums that are more average 
int moreAverageAmount(int * arr, int size, float avrg);
// sum of elements modules
int sumOfModules(int * arr, int size);

int main() {
    srand(time(0));
    int N;
    printf("Enter the size of the array:");
    scanf("%d", &N);
    if (N > 0) {
        int arr[N];
        generateArray(&arr[0], N);
        float avrg = findAverage(&arr[0], N);
        printf("Average number: %.2f\n", avrg);
        moreAverageAmount(&arr[0], N, avrg);
        printf("Sum of elements modules after first negative num: %d\n", sumOfModules(&arr[0], N));
    } else {
        printf("Error! Size need be more 1!\n");
    }
}

void generateArray(int * arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        // generate random value from -100 to 100
        arr[i] = rand() % 201 - 100;
        printf(" %d", arr[i]);
    }
    printf(" ]\n");
}

float findAverage(int * arr, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}

int moreAverageAmount(int * arr, int size, float avrg) {
    int amount = 0;
    printf("[");
    for (int i = 0; i < size; i++) {
        if (arr[i] > avrg) {
            amount++;
            printf(" %d", arr[i]);
        }
    }
    printf(" ]\n");
    return amount;
}

int sumOfModules(int * arr, int size) {
    int sum = 0;
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] < 0) {
            for (int j = i + 1; j < size; j++) {
                sum += abs(arr[j]);
            }
            break;
        }
    }
    return sum;
}