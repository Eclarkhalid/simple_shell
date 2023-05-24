#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
#define TOKEN_DELIMITERS " \t\r\n\a"

/**
 * tokenize_input - Tokenizes the input command line
 * @input: The input command line string
 *
 * Return: An array of tokens
 */
char **tokenize_input(char *input)
{
    int buffer_size = BUFFER_SIZE;
    int position = 0;
    char **tokens = malloc(buffer_size * sizeof(char *));
    char *token;
    
    if (!tokens)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    
    token = strtok(input, TOKEN_DELIMITERS);
    while (token)
    {
        tokens[position] = token;
        position++;
        
        if (position >= buffer_size)
        {
            buffer_size += BUFFER_SIZE;
            tokens = realloc(tokens, buffer_size * sizeof(char *));
            
            if (!tokens)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
        
        token = strtok(NULL, TOKEN_DELIMITERS);
    }
    
    tokens[position] = NULL;
    return tokens;
}

/**
 * execute_command - Executes the given command with arguments
 * @args: The array of command line arguments
 */
void execute_command(char **args)
{
    execvp(args[0], args);
    
    perror(args[0]);
    exit(EXIT_FAILURE);
}

/**
 * main - Entry point of the program
 *
 * Return: 0 on success
 */
int main(void)
{
    char buffer[BUFFER_SIZE];
    ssize_t n_read;
    pid_t pid;
    int status;
    char **args;
    
    while (1)
    {
        printf("#cisfun$ ");
        
        n_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (n_read == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        
        if (n_read == 0)
            break;
        
        buffer[n_read - 1] = '\0';
        args = tokenize_input(buffer);
        
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        
        if (pid == 0)
        {
            execute_command(args);
        }
        else
        {
            waitpid(pid, &status, 0);
        }
        
        free(args);
    }
    
    printf("\n");
    return (0);
}

