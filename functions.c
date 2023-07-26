#include "shell.h"

/**
* free_tokens - free memory allocated to tokens
*
* @tokens: array of tokens
*/
void free_tokens(char **tokens)
{
int i = 0;

while (tokens[i])
{
free(tokens[i]);
i++;
}
}

/**
* execute_command - executes commands
*
* @tokens: array of tokens
* @buffer: input buffer
* Return: exit_status
*/
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
return (exit_status);
}
/**
* get_environment_variable - get the value of an environment variable
* @name: name of the environment variable
* Return: value of the environment variable or NULL if not found
*/
char *get_environment_variable(char *name)
{
int i = 0;
size_t name_len = _strlen(name);

for (; environ[i]; i++)
{
if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
return (&environ[i][name_len + 1]);
}

return (NULL);
}

/**
* find_command_path - search for the command in the directories listed in PATH
* @command: command to find
* Return: pointer to the command's path or NULL if not found
*/
char *find_command_path(char *command)
{
char *path, *path_copy, *path_token, *command_path;
int command_length, directory_length;
struct stat buffer;

path = get_environment_variable("PATH");
if (path)
{
path_copy = _string_duplicate(path);
command_length = _strlen(command);
path_token = strtok(path_copy, ":");
while (path_token)
{
directory_length = _strlen(path_token);
command_path = malloc(command_length + directory_length + 2);
_string_copy(command_path, path_token);
_string_concatenate(command_path, "/");
_string_concatenate(command_path, command);
_string_concatenate(command_path, "\0");
if (stat(command_path, &buffer) == 0)
{
free(path_copy);
return (command_path);
}
else
{
free(command_path);
path_token = strtok(NULL, ":");
}
}
free(path_copy);
if (stat(command, &buffer) == 0) /*If the comd is found in the current dir*/
{
return (command);
}
return (NULL);
}
return (NULL);
}

/**
* tokenize_input - tokenize the input buffer
* @buffer: input buffer
* @tokens: array to store tokens
*/
void tokenize_input(char *buffer, char **tokens)
{
size_t token_len;
const char *delim = " \t\n";
char *token = NULL;
int count = 0;
char *buffer_copy = NULL;
buffer_copy = _string_duplicate(buffer);
token = strtok(buffer_copy, delim);
for (count = 0; token; count++)
{
token_len = _strlen(token);
tokens[count] = malloc(sizeof(char *) * (token_len + 1));
_strncpy(tokens[count], token, token_len + 1);
token = strtok(NULL, delim);
}
free(buffer_copy);
}
