#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <ctype.h>

extern char **environ;

int _atoi(char *ntr);
int env_func(void);
int exit_func(char **tokens, char *buffer);
int handle_builtin(char **tokens, char *buffer);
void free_av(char **av);
void free_tokens(char **tokens);
void tokenize_input(char *buffer, char **tokens);
void _puts(char *str);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(char *name);
int check_spaces_around_command(char *input);
int check_spaces_tabs(char *str);
int execute_cmd(char **av, char *buff);
char *_getenv(char *name);
char* find_command_path(char *command);
char *get_environment_variable(char *name);
char *find_command_path(char *command);
size_t _string_length(const char *str);
char *_string_concatenate(char *dest, char *src);
char *_get_cmp(char *name);
char *_string_copy(char *dest, const char *src);
char *_string_duplicate(const char *str);
char *_memcpy(char *dest, char *src, unsigned int n);
void *_memory_copy(void *dest, const void *src, size_t n);
char *_strncpy(char *dest, char *src, int n);
void tokenize(char *buffer, char **tokens);
int _putchar(char c);

#endif
