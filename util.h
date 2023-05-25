#ifndef UTIL_H
#define UTIL_H

typedef struct Alias
{
    char *name;
    char *value;
} Alias;

void add_alias(char *name, char *value);
void print_alias(char *name);
char *replace_variables(char *line, int status);
char *str_replace(char *str, const char *old, const char *new);
char **tokenize_input(char *input);
void free_tokens(char **tokens);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);

#endif /* UTIL_H */

