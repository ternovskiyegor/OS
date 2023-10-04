#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    float data;
    struct node * next;
} Node;

typedef struct list {
    int size;
    Node * head;
} LinkedList;

// ініціалізація LinkedList
LinkedList * new_list();
// додати елемент у кінець списку
void add(LinkedList * list, float data);
// вставка елементу до середини списку
void insert(LinkedList * list, int index, float data);
// отримати кількість елементів у списку
int size(LinkedList * list);
// видалення елементу за індексом
void remove(LinkedList * list, int index);
// free memory
void free_list(LinkedList * list);
// отримати значення заданного елементу
float get(LinkedList * list, int index);
// знаходження останього елементу
Node * findLastNode(LinkedList * list);
// check index bounds
int checkIndex(LinkedList * list, int index);
// print all list
void printList(LinkedList * list);

int main() {
    LinkedList * list = new_list();
    int choice;
    while(1) {
        printf("Select action:\n");
        printf("1) Add number to list\n");
        printf("2) Insert number to list\n");
        printf("3) Remove number from list\n");
        printf("4) Get element of list\n");
        printf("5) Get size of list\n");
        printf("6) Print list\n");
        printf("7) Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            float num;
            printf("Enter the num: ");
            scanf("%f", &num);
            add(list, num);
        } else if (choice == 2) {
            float num;
            int idx;
            printf("Enter the num: ");
            scanf("%f", &num);
            printf("Enter index: ");
            scanf("%d", &idx);
            insert(list, idx, num);
        } else if (choice == 3) {
            int idx;
            printf("Enter index: ");
            scanf("%d", &idx);
            remove(list, idx);
        } else if (choice == 4) {
            int idx;
            printf("Enter index: ");
            scanf("%d", &idx);
            printf("Your element is: %.2f\n", get(list, idx));
        } else if (choice == 5) {
            printf("Current size of list: %d\n", size(list));
        } else if (choice == 6) {
            printf("Your list:\n");
            printList(list);
        } else if (choice == 7) {
            free(list);
            break;
        } else  {
            printf("Invalid command!\n");
        }   
    }
    return 0;
}

LinkedList * new_list() {
    LinkedList * list = (LinkedList*)malloc(sizeof(LinkedList));
    list->size = 0;
    list->head = NULL;
    return list;
}

void add(LinkedList * list, float data) {
    Node * new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    if (size(list) == 0) {
        list->head = new_node;
    } else {
        // find last node
        Node * lastNode = findLastNode(list);
        // set new last node
        lastNode->next = new_node;
    }
    list->size++;
}

void insert(LinkedList * list, int index, float data) {
    if (checkIndex(list, index)) {
        Node * new_node = (Node*)malloc(sizeof(Node));
        new_node->data = data;
        if (index == 0) {
            new_node->next = list->head;
            list->head = new_node;
        } else {
            Node * current_node = list->head;
            for (int i = 0; i < list->size; i++) {
                if (i + 1 == index) {
                    Node * next_node = current_node->next;
                    new_node->next = next_node;
                    current_node->next = new_node;
                    break;
                }
                current_node = current_node->next;
            }
        }
        list->size++;
    }
}

int size(LinkedList * list) {
    return list->size;
}

void remove(LinkedList * list, int index) {
    if (checkIndex(list, index)) {
        Node * node_to_remove;
        if (index == 0) {
            node_to_remove = list->head;
            list->head = list->head->next;
        } else {
            Node * current = list->head;
            for (int i = 0; i < index-1; i++) {
                current = current->next;
            }
            node_to_remove = current->next;
            current->next = current->next->next;
        }
        free(node_to_remove);
        list->size--;
    }   
}

float get(LinkedList * list, int index) {
    if (checkIndex(list, index)) {
        Node * current = list->head;
        for(int i = 0; i < list->size; i++) {
            if (i == index) {
                return current->data;
            }
            current = current->next;
        }
    }
    return 0;
}

void free_list(LinkedList * list) {
    Node * current_node = list->head;
    while (current_node != NULL) {
        Node * next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    free(list);
}

int checkIndex(LinkedList * list, int index) {
    if (index >= 0 && index < list->size) {
        return 1;
    }
    printf("Error! Index is out of range!\n");
    return 0;
}

Node * findLastNode(LinkedList * list) {
    Node * currentNode = list->head;
    while(currentNode->next != NULL) {
        currentNode = currentNode->next;
    }
    return currentNode;
}

void printList(LinkedList * list) {
    Node * current_node = list->head;
    while(current_node != NULL) {
        printf("%.2f", current_node->data);
        if (current_node->next != NULL) {
            printf("->");
        }
        current_node = current_node->next;
    }
    printf("\n");
}