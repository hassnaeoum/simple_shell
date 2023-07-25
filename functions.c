#include "shell.h"

/* Free memory allocated to tokens */
void free_tokens(char **tokens)
{
int i = 0;

while (tokens[i])
{
free(tokens[i]);
i++;
}
}

/* Execute commands */
int execute_command(char **tokens, char *buffer)
{
pid_t pid;
char *cmd_path = NULL;
int exit_status = handle_builtin(tokens, buffer);

if (exit_status == -1)
{
cmd_path = find_command_path(tokens[0]);
if (!cmd_path)
{
_puts("Command not found"); /* Custom error message */
return (2);
}

pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}

if (pid == 0)
{
if (execve(cmd_path, tokens, environ) == -1)
{
perror("execve");
free_tokens(tokens);
free(buffer);
exit(2);
}
}
else
{
waitpid(pid, &exit_status, 0);
if (exit_status != 0)
exit_status = 2;
}

if (_strcmp(cmd_path, tokens[0]) != 0)
free(cmd_path);
}

return exit_status;
}

/* Get the value of an environment variable */
char *get_environment_variable(char *name)
{
int i = 0;
size_t name_len = _strlen(name);

for (; environ[i]; i++)
{
if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
return (&environ[i][name_len + 1]);
}

return NULL;
}

/* Search for the command in the directories listed in PATH */
char *find_command_path(char *command)
{
char *path, *path_copy, *path_token, *command_path;
int command_length, directory_length;
struct stat buffer;

path = get_environment_variable("PATH");
if (path)
{
path_copy = _strdup(path);
command_length = _strlen(command);
path_token = strtok(path_copy, ":");

while (path_token)
{
directory_length = _strlen(path_token);
command_path = malloc(command_length + directory_length + 2);
_strcpy(command_path, path_token);
_strcat(command_path, "/");
_strcat(command_path, command);
_strcat(command_path, "\0");

if (stat(command_path, &buffer) == 0)
{
free(path_copy);
return command_path;
}
else
{
free(command_path);
path_token = strtok(NULL, ":");
}
}

free(path_copy);

if (stat(command, &buffer) == 0) /* If the command is found in the current directory */
{
return command;
}

return NULL;
}

return NULL;
}

/* Tokenize the input buffer */
void tokenize_input(char *buffer, char **tokens)
{
size_t token_len;
const char *delim = " \t\n";
char *token = NULL;
int count = 0;
char *buffer_copy = NULL;

buffer_copy = _strdup(buffer);
token = strtok(buffer_copy, delim);

for (count = 0; token; count++)
{
token_len = _strlen(token);
tokens[count] = malloc(sizeof(char *) * token_len);
_strncpy(tokens[count], token, token_len + 1);
token = strtok(NULL, delim);
}

free(buffer_copy);
}
