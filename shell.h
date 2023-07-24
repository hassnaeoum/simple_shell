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
int _putchar(char c);


#endif
