#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float play(float bet);
int areNumsTheSame(int * arr, int size);
int isContains7(int * arr, int size);
int isThreeRepeat(int * arr, int size);

int main() {
    srand(time(0));
    float bet, totalAmount = 700;
    int choice;
    while (1) {
        printf("\nTotal balance: %.2f $\n\n", totalAmount);
        printf("Choose action:\n  1)Play\n  2)Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Enter your bet ($): ");
            scanf("%f", &bet);
            if (bet > totalAmount) {
                printf("Insufficient funds!\n");
            } else if (bet > 0) {
                totalAmount -= bet;
                float winsize = play(bet);
                if (winsize > bet) {
                    printf("YUUHUU! YOU WIN!\n");
                    printf("  + %.2f $\n", winsize);
                    totalAmount += winsize;
                } else if (winsize == bet) {
                    printf("YOU HAVE YOUR MONEY BACK!");
                    totalAmount += winsize;
                } else {
                    printf("YOU LOSE :(\n");
                }
            } else {
                printf("Bet can`t be less 1.00$!\n");
            }
        } else if (choice == 2) {
            break;
        } else {
            printf("Incorrect value!\n");
        }
    }
    return 0;   
}

int areNumsTheSame(int * arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] != arr[i + 1]) {
            return 0;
        }
    }
    return 0;
}

int isContains7(int * arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] == 7) {
            return 1;
        }
    }
    return 0;
}

int isThreeRepeat(int * arr, int size) {
    int amount = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                amount++;
            }
        }   
        if (amount >= 2) {
            return 1;
        }
        amount = 0;
    }
    return 0;
}

float play(float bet) {
    int arr[6];
    int counter = 0;
    printf("[ ");
    for (int i = 0; i < 6; i++) {
        arr[i] = rand() % 10 + 1;
        if (arr[i] == 7) {
            counter++;
        }
        if (i != 5) {
            printf(" %d |", arr[i]);
        } else {
            printf(" %d ]\n", arr[i]);
        }
    }
    if (areNumsTheSame(&arr[0], 6)) {
        if (arr[0] == 7) {
            return 3 * bet;
        }
        return 2 * bet;
    } else if (isContains7(&arr[0], 6)) {
        return bet;
    } else if (isThreeRepeat(&arr[0], 6)) {
        return bet;
    } else {
        return -1 * bet;
    }
}