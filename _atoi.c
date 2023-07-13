#include <stdio.h>
#include <unistd.h>
#include "shell.h"
/**
* isatoi - converts a string to an integer
* @str: the string to be converted
* Return: 0 if no numbers in the string, converted number otherwise
*/
int isatoi(char *str)
{
int sign = 1;
int result = 0;
if (str[0] == '-')
{
sign = -1;
str++; /* Move the pointer to the next character*/
}
for (int h = 0; str[h] != '\0'; h++)
{
if (str[h] >= '0' && str[h] <= '9')
{
result = result * 10 + (str[h] - '0');
}
else
{
break;
}
}
return (sign *result);
}
/**
* isDelimiter - checks if a character is a delimiter
* @c: the character to check
* @delim: the delimiter string
* Return: 1 if the character is a delimiter, 0 otherwise
*/
int isDelimiter(char c, char *delim)
{
int i = 0;
while (delim[i] != '\0')
{
if (delim[i] == c)
{
return (1);
}
i++;
}
return (0);
}
/**
* isAlphabetic - checks for an alphabetic character
* @c: The character to check
* Return: 1 if 'c' is an alphabetic character, 0 otherwise
*/
int isAlphabetic(int c)
{
return (isalpha(c) != 0);
}
/**
* isInteractive - checks if the shell is in interactive mode
* @info: struct address
* Return: 1 if the shell is in interactive mode, 0 otherwise
*/
int isInteractive(info_t *info)
{
if (isatty(STDIN_FILENO))
{
if (info->readfd <= 2)
{
return (1);
}
}
return (0);
}
