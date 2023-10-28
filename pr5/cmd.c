#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <windows.h>
#include <unistd.h>

int main() {
    char buffer[127]; // buffer for the command entered by user
    char username[256];
    DWORD username_len = sizeof(username);
    while (1) {
        printf("egor$");
        //fgets(buffer, size_t(buffer), stdin);
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        if(strcmp(buffer, "stop") == 0) {
            return 0;
        } else if (strcmp(buffer, "--help") == 0 || strcmp(buffer, "-h") == 0) {
            printf("help menu\n");
        } else {
            system(buffer);
        }
        printf("%s\n", buffer);
    } 
    return 1;
}