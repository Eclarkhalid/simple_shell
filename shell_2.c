#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
#define MAX_PATH_LENGTH 100

void parseCommand(char* command, char** arguments) {
    char* token = strtok(command, " \t\n");
    int argIndex = 0;
    while (token != NULL && argIndex < MAX_ARGUMENTS) {
        arguments[argIndex] = token;
        argIndex++;
        token = strtok(NULL, " \t\n");
    }
    arguments[argIndex] = NULL;
}

int commandExists(char* command, char* directory) {
    char path[MAX_PATH_LENGTH];
    snprintf(path, sizeof(path), "%s/%s", directory, command);
    return access(path, X_OK) == 0;
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    char* arguments[MAX_ARGUMENTS];
    char* path = getenv("PATH");
    int commandFound = 0;
    char* directory;
    pid_t pid;

    while (1) {
        printf(":) ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            break;
        }

        if (command[0] == '\n')
            continue;

        command[strcspn(command, "\n")] = '\0';

        parseCommand(command, arguments);

        commandFound = 0;
        directory = strtok(path, ":");
        while (directory != NULL) {
            if (commandExists(arguments[0], directory)) {
                commandFound = 1;
                break;
            }
            directory = strtok(NULL, ":");
        }

        if (!commandFound) {
            printf("Command not found: %s\n", arguments[0]);
            continue;
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            execvp(arguments[0], arguments);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
        }
    }

    return 0;
}

