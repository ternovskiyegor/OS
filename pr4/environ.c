#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// print all env
void print_env();
// -h or --help
void print_help();
// -i <var> or --info <var>
void var_info(char * var);
// -a <var> -v <value>
// --assign <var> --value <value>
void new_value(char * var, char * value);
// -d <var> or --del <var>
void del_var(char * var);
// -c or --clear
void clear_env();

int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_env();
        return 1;
    }
    int i = 1;
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
        print_help();
    } else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--info") == 0) {
        if (i + 1 < argc) {
            char * var_name = argv[i + 1];
            var_info(var_name);
        }
    } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--set") == 0) {
        if (i + 1 < argc) {
            char * var_name = strtok(argv[i + 1], "=");
            char * var_value = strtok(NULL, "=");
            new_value(var_name, var_value);
        }
    } else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--assign") == 0) {
        if (i + 1 < argc && strcmp(argv[i], "-v") != 0 && strcmp(argv[i], "--value") != 0) {
            char * var_name = argv[i + 1];
            if (i + 2 < argc) {
                if (strcmp(argv[i + 2], "-v") == 0 || strcmp(argv[i + 2], "--value") == 0) {
                    if (i + 3 < argc) {
                        char * var_value = argv[i + 3];
                        new_value(var_name, var_value);
                    } else {
                        char var_value[2] = " ";
                        new_value(var_name, var_value);
                    }
                }
            }
        } else {
            printf("Error! Use -h or --help for correct usage of program!\n");
        }
    } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--del") == 0) {
        if (i + 1 <= argc) {
            char * name = argv[i + 1];
            del_var(name);
        }
    } else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--clear") == 0) {
        clear_env();
    }
    return 0;
}

void print_env() {
    extern char ** environ;
    int i = 0;
    while (environ[i] != NULL) {
        printf("%s\n", environ[i]);
        i++;
    }
}

void print_help() {
    printf("Usage of the environ program:\n");
    printf("  -h,    --help                          print help message;\n");
    printf("  -i,    --info <var>                    print variable info;\n");
    printf("  -s,    --set <var=value>               set new value of var;\n");
    printf("  -a -v, --assign <var> --value <value>  set var new value;\n");
    printf("  -d,    --del <var>                     pdelete variable from env;\n");
    printf("  -c,    --clear                         clear all environment;\n");
}

void var_info(char * var) {
    if (getenv(var) != NULL) {
        printf("%s=%s\n", var, getenv(var));
    } else {
        printf("ERROR! There isn`t var with this name!\n");
    }
}

void new_value(char * var, char * value) {
    printf("Current value of var:\n");
    var_info(var);
    if (setenv(var, value, 1) != 0) {
        printf("Something went wrong!\n");
        return;
    }
    printf("New value of the var:\n");
    printf("%s=%s\n", var, getenv(var));
}

void del_var(char * var) {
    if (unsetenv(var) == 0) {
        printf("%s was cleared!\n", var);
    } else {
        printf("Error!\n");
    }
    printf("Updated vars list:\n");
    print_env();
}

void clear_env() {
    clearenv();
    printf("All env was cleared!\n");
}