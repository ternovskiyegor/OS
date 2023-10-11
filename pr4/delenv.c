#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    extern char ** environ;
    int i = 0;
    if (argc >= 2) {
        if (unsetenv(argv[1]) == 0) {
            printf("Deleted successfully!\n");
        } else {
            printf("Error!\n");
            exit(0);
        }
    } else {
        if (clearenv() != 0) {
            printf("Error!\n");
            exit(0);
        } 
    }
    printf("List of env vars:\n");
    i = 0;
    while (environ[i] != NULL) {
        printf("%s\n", environ[i++]);
    }
}