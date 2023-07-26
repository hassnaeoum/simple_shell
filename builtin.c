#include "shell.h"

/**
 * _atoi - converts string to an integer
 * @ntr: string to be converted
 * Return: converted integer value or -1
 */
int _atoi(char *ntr)
{
	int i = 0, n = 0;

	if (ntr[i] == '+')
		i++;

	while (ntr[i])
	{
		if (ntr[i] < '0' || ntr[i] > '9')
			return (-1);

		n = (n * 10) + (ntr[i] - '0');
		i++;
	}

	return (n);
}
/**
 * handle_builtin - handle builtin commands
 * @tokens: tokens
 * @buffer: buffer
 * Return: int
 */
int handle_builtin(char **tokens, char *buffer)
{
	if (_strcmp(tokens[0], "exit") == 0)
		return (exit_func(tokens, buffer));
	else if (_strcmp(tokens[0], "env") == 0)
		return (env_func());
	/*
	 *else if (_strcmp(tokens[0], "setenv") == 0)
	 *	return (_setenv());
	 *else if (_strcmp(tokens[0], "unsetenv") == 0)
	 *	return (_unsetenv(tokens[1]));
	 */
	else
		return (-1);
}
/**
 * env_func - get the env
 * return: always 0
 */
int env_func(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		_puts(environ[i]);

	return (0);
}
/**
 * exit_func - does the exiting
 * @tokens: tokens
 * @buffer: buffer
 * Return: integer
 */
int exit_func(char **tokens, char *buffer)
{
	int i = 0;
	int existatus = 0;

	while (tokens[i])
		i++;
	if (i == 1)
	{
		free_av(tokens);
		free(buffer);
		exit(0);
	}
	if (_atoi(tokens[1]) == -1)
	{
		fprintf(stderr, "./hsh: 1: exit: Illegal number: %s\n", tokens[1]);
		return (2);
	}
	existatus = atoi(tokens[1]);
	free_av(tokens);
	free(buffer);
	exit(existatus);
}
