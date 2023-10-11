#include <stdio.h>
#include <stdlib.h>

int main() {
    extern char ** environ;
    int i = 0;
    // print all variables
    while (environ[i] != NULL) {
        printf("%s\n", environ[i++]);
    }
    // print variable using getenv() func
    printf("\n\nList of environment variables (main):\n");
    printf("SHELL=%s\n", getenv("SHELL"));
    printf("LANGUAGE=%s\n", getenv("LANGUAGE"));
    printf("USERNAME=%s\n", getenv("USERNAME"));
    printf("HOME=%s\n", getenv("HOME"));
    printf("PWD=%s\n", getenv("PWD"));
    return 0;
}