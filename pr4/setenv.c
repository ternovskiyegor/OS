#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc >= 3) {
        char * name = argv[1];
        char * value = argv[2];
        if (setenv(name, value, 1) != 0) {
            printf("Something went wrong!\n");
            exit(0);
        }
        printf("Current value of the var:\n");
        printf("%s=%s\n", name, getenv(name));
    } else {
        printf("Error! Incorrect formal!\n");
        printf("Use next format:\n\t./program-name name value\n");
    }
    return 0;
}