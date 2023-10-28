#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        if (unsetenv(argv[1]) == 0) {
            printf("Deleted successfully!\n");
        } else {
            printf("Error!\n");
            exit(0);
        }
    } else {
        clearenv();
        printf("All env vars was deleted!\n");
    }
    extern char ** environ;
    int i = 0;
    printf("List of env vars:\n");
    while (environ[i] != NULL) {
        printf("%s\n", environ[i]);
        i++;
    }
    return 0;
}