#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[10];
    char surname[13];
    int age;
} student;

void printStudents(student * students, int size);
void addStudent(student ** students, int size);

int main() {
    int size = 0, choice;
    student *students = (student*)malloc(size * sizeof(student));
    while (1) {
        printf("\nChoose the action:\n");
        printf("1) Add student\n");
        printf("2) Print all students\n");
        printf("3) Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        printf("\n");
        if (choice == 1) {
            size++;
            addStudent(&students, size);
        } else if (choice == 2) {
            printStudents(students, size);
        } else if (choice == 3) {
            break;
        } else {
            printf("Error! Unknown command.\n");
        }
    }
    free(students);
    return 0;
}

void printStudents(student * students, int size) {
    if (size == 0) {
        printf("The list of students is empty!\n");
        return;
    }
    int i;
    printf("Total amount: %d\n", size);
    printf("Num |    Name    |    Surname    | Age |\n");
    for (i = 0; i < size; i++) {
        printf(" %2d | %10s | %13s |  %2d |\n", i + 1, students[i].name,  students[i].surname, students[i].age);
    }
}

void addStudent(student ** students, int size) {
    *students = (student*)realloc(*students, size * sizeof(student));
    printf("Enter name: ");
    scanf("%s", (*students)[size - 1].name);
    printf("Enter surname: ");
    scanf("%s", (*students)[size - 1].surname);
    printf("Enter age: ");
    scanf("%d", &(*students)[size - 1].age);
    printf("Added successfully!\n");
}