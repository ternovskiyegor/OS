#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]) {
    if (argc > 1) {
        char * commands = argv[1];
        char * command = strtok(commands, ";");
        while (command != NULL) {
            printf("Result of the '%s' command:\n", command);
            int res = system(command);
            command = strtok(NULL, ";");
        }
    } else {
        printf("Error!\nUse: %s 'command1;command2'\n", argv[0]);
    }
}