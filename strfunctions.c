#include <stdio.h>
#include <stddef.h>
#include <stdlib.h> /* Include the necessary header for malloc*/
#include "shell.h"
/**
* _strlen - calculates the length of a string.
* @str: pointer to a string.
* Return: Length of the string.
*/
int _strlen(char *str)
{
int i = 0;
while (str[i])
i++;
return (i);
}
/**
* _strcat  - concatenate two strings
*
* @dest: destination string
* @src: source string
* Return: Pointer to the concatenated string.
*/
char *_strcat(char *dest, char *src)
{
int i = 0, j = 0;
while (dest[i] != '\0')
{
i++;
}
while (src[j] != '\0')
{
dest[i] = src[j];
i++;
j++;
}
dest[i] = '\0';
return (dest);
}
/**
* _strcpy - copies str to another
* @dest: destination string
* @src: the string that we're going to copy
* Return: Pointer to the destination string.
*/
char *_strcpy(char *dest, char *src)
{
int i = 0;
while (*(src + i))
{
*(dest + i) = *(src + i);
i++;
}
*(dest + i) = '\0';
return (dest);
}
/**
* _strdup- duplicate str and return a pointer to newly allocated str
* @str: pointer to be duplicated.
* Return: Pointer to the duplicated string or NULL if memory allocation fails.
*/
char *_strdup(char *str)
{
	char *str1;
	unsigned int len;

	if (str == 0)
	{
		return (NULL);
	}
	len = _strlen(str) + 1;
	str1 = (char *)malloc(sizeof(char) * len);
	if (str1 == 0)
	{
		return (NULL);
	}
	_memcpy(str1, str, len);
	return (str1);
}
/**
* _memory_copy - function that copies memory area.
* @dest: destination memory area.
* @src: source memory area.
* @n: number of bytes to be copied.
* Return: Pointer to the destination memory area.
*/
void *_memory_copy(void *dest, const void *src, int n)
{
char *d = (char *)dest;
const char *s = (const char *)src;
size_t i;
for (i = 0; i < n; i++)
{
d[i] = s[i];
}
return (dest);
}
