#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int size;
    int * array;
} ArrayList;

// initialization of ArrayList
ArrayList * newArrayList();
// add element in the end ot array
void add(ArrayList * list, int item);
// add element int the middle of array
void insert(ArrayList * list, int index, int item);
// get array size
int size(ArrayList * list);
// remove element from the array by index
void remove(ArrayList * list, int index);
// set new value of element
void set(ArrayList * list, int index, int item);
// get element by index
int get(ArrayList * list, int index);
// check index bounds
int checkIndex(ArrayList * list, int index);
// print ArrayList
void printList(ArrayList * list);

int main() {
    ArrayList * arr1 = newArrayList();
    int num;
    int n;
    printf("Enter start size of arr (4+): ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter num to add (at the end): ");
        scanf("%d", &num);
        add(&arr1[0], num);
    }
    printf("Your ArrayList:\n");
    printList(&arr1[0]);
    printf("Insert element '5' at [2] index");
    insert(&arr1[0], 2, 5);
    printList(&arr1[0]);
    printf("Remove element at [3] index:");
    remove(&arr1[0], 3);
    printList(&arr1[0]);
    printf("Get element with index [1]: %d\n", get(&arr1[0], 1));
    printf("Set element with index [1] new value (11): ");
    set(&arr1[0], 1, 11);
    printList(&arr1[0]);
    printf("Current size of the array: %d\n", size(&arr1[0]));
    return 0;
}

ArrayList * newArrayList() {
    ArrayList * list = (ArrayList *)malloc(sizeof(ArrayList));
    list->size = 0;
    list->array = (int *)malloc(sizeof(int));
    return list;
}

void add(ArrayList * list, int item) {
    list->size++;
    list->array = (int *)realloc(list->array, sizeof(int) * list->size);
    list->array[list->size - 1] = item;
}

void insert(ArrayList * list, int index, int item) {
    if (checkIndex(&list[0], index)) {
        list->size++;
        list->array = (int *)realloc(list->array, sizeof(int) * list->size);
        for (int i = list->size - 1; i > index; i--) {
            list->array[i] = list->array[i - 1];
        }
        list->array[index] = item;
    }
}

int size(ArrayList * list) {
    return list->size;
}

void remove(ArrayList * list, int index) {
    if (checkIndex(&list[0], index)) {
        for (int i = index; i < list->size - 1; i++) {
            list->array[i] = list->array[i + 1];
        }
        list->size--;
        list->array = (int *)realloc(list->array, sizeof(int) * list->size);
    }
}

void set(ArrayList * list, int index,int item) {
    if (checkIndex(&list[0], index)) {
        list->array[index] = item;
    }
}

int get(ArrayList * list, int index) {
    if (checkIndex(&list[0], index)) {
        return list->array[index];
    }
    return 0;
}

int checkIndex(ArrayList * list, int index) {
    if (index >= 0 && index < list->size) {
        return 1;
    }
    printf("Error! Index is out of range!\n");
    return 0;
}

void printList(ArrayList * list) {
    printf("[");
    for (int i = 0; i < list->size; i++) {
        printf(" %d", list->array[i]);
    }
    printf(" ]\n");
}