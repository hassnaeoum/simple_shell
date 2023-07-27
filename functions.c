#include "shell.h"

/**
 * free_av - free the tokens
 *
 * @av: tokens
 */
void free_av(char **av)
{
	int i = 0;

	while (av[i])
	{
		free(av[i]);
		i++;
	}
}

/**
* execute_cmd - executes commands
*
* @av:tokens
* @buffer: input buffer
* Return: exit_status
*/
int execute_cmd(char **av, char *buffer)
{
pid_t pid;
char *cmd = NULL;
int exit_status = handle_builtin(av, buffer);
if (exit_status == -1)
{
cmd  = get_cmd(av[0]);
if (!cmd)
{
_puts("Command not found");
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
if (execve(cmd, av , environ) == -1)
{
perror("execve");
free_av(av);
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
if (_strcmp(cmd, av[0]) != 0)
free(cmd);
}
return (exit_status);
}
/**
* _getenv - get the value of an env variable
* @name: name of the env variable
* Return: ptr
*/
char *_getenv(char *name)
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
* get_cmd - search for the command in the directories listed in PATH
* @command: command to find
* Return: ptr
*/
char *get_cmd(char *command)
{
char *path, *path_copy, *path_token, *file_path;
int command_length, directory_length;
struct stat buffer;

path = _getenv("PATH");
if (path)
{
path_copy = _strdup(path);
command_length = _strlen(command);
path_token = strtok(path_copy, ":");
while (path_token)
{
directory_length = _strlen(path_token);
file_path = malloc(command_length + directory_length + 2);
_strcpy(file_path, path_token);
			_strcat(file_path, "/");
			_strcat(file_path, command);
			_strcat(file_path, "\0");
			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);
		if (stat(command, &buffer) == 0)
		{
			return (command);
		}
		return (NULL);
	}
return (NULL);
}

/**
* tokenize - tokenize the input buffer
* @buffer: buffer
* @tokens: tokens
*/
void tokenize(char *buffer, char **tokens)
{
size_t token_len;
const  char *delim = " \t\n";
char *token = NULL;
int count = 0;
char *buffer_copy = NULL;
buffer_copy = _strdup(buffer);
token = strtok(buffer_copy, delim);
for (count = 0; token; count++)
{
token_len = _strlen(token);
tokens[count] = malloc(sizeof(char *) * token_len);
token = strtok(NULL, delim);
}
free(buffer_copy);
}
