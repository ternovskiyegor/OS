#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>

int main() {
    char hostname[1024];
    printf("\ngethostname() func example:\n");
    if (gethostname(hostname, 1023) == 0) {
        printf("Hostname: %s\n\n", hostname);
    } else {
        printf("Error!\n\n");
    }
    printf("uname() func example:\n\n");
    struct utsname unameData;
    uname(&unameData);
    printf("Sysname: %s\n", unameData.sysname);
    printf("Machine: %s\n", unameData.machine);
    printf("Version: %s\n", unameData.version);
    printf("Nodename: %s\n", unameData.nodename);
    printf("Release: %s\n", unameData.release);
}