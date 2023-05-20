#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

void prompt() {
    printf("$ ");
    fflush(stdout);
}

void execute_command(char *command) {
    char *args[MAX_COMMAND_LENGTH];
    char *token;

    int i = 0;
    token = strtok(command, " \t\n");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;

    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
        printf("Command not found: %s\n", args[0]);
        exit(1);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("Fork failed");
        exit(1);
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        prompt();
        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            exit(0);
        }
        execute_command(command);
    }

    return 0;
}

