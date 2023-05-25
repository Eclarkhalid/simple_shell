#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define BUFFER_SIZE 1024
#define MAX_ARGS 64
char *get_path_command(char *command) {
char *path_env = getenv("PATH");
char *token;
char *path;
token = strtok(path_env, ":");
while (token != NULL) {
path = malloc(strlen(token) + strlen(command) + 2);
sprintf(path, "%s/%s", token, command);
if (access(path, X_OK) == 0)
return path;
free(path);
token = strtok(NULL, ":");
}
return NULL;
}
int main(void) {
char input[BUFFER_SIZE];
char *prompt = "#cisfun$ ";
pid_t pid;
char inputCopy[BUFFER_SIZE];
while (1) {
char *args[MAX_ARGS];
int argCount = 0;
char *token;
char *command;
char *path_command;
printf("%s", prompt);
if (fgets(input, sizeof(input), stdin) == NULL) {
printf("\n");
break;
}
input[strcspn(input, "\n")] = '\0';
if (strlen(input) == 0)
continue;
strcpy(inputCopy, input);
token = strtok(inputCopy, " ");
while (token != NULL && argCount < MAX_ARGS - 1) {
args[argCount++] = token;
token = strtok(NULL, " ");
}
args[argCount] = NULL;
command = args[0];
path_command = get_path_command(command);
pid = fork();
if (pid < 0) {
perror("Fork failed");
exit(EXIT_FAILURE);
} else if (pid == 0) {
if (path_command != NULL) {
if (execvp(path_command, args) == -1) {
fprintf(stderr, "%s: command not found\n", command);
exit(EXIT_FAILURE);
}
} else {
fprintf(stderr, "%s: command not found\n", command);
exit(EXIT_FAILURE);
}
} else {
waitpid(pid, NULL, 0);
}
free(path_command);
}
return (0);
}
