#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

int main() {
    struct passwd * userData;
    uid_t user_uid = getuid();
    userData = getpwuid(user_uid);
    printf("User ID: %d\n", userData->pw_uid);
    printf("Username: %s\n", userData->pw_name);
    printf("User full name: %s\n", userData->pw_gecos);
    printf("User login dir: %s\n", userData->pw_dir);
    printf("User password: %s\n", userData->pw_passwd);
    // info about root
    struct passwd * user_root = getpwnam("root");
    printf("\n\nInfo about root user:\n");
    printf("User ID: %d\n", user_root->pw_uid);
    printf("Username: %s\n", user_root->pw_name);
    printf("User full name: %s\n", user_root->pw_gecos);
    printf("User login dir: %s\n", user_root->pw_dir);
    printf("User password: %s\n", user_root->pw_passwd);
    return 0;
}