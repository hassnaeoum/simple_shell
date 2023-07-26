#include <stdio.h>
#include <stddef.h>
#include "shell.h"
/**
* _string_length - calculates the length of a string.
* @str: pointer to a string.
* Return: Length of the string.
*/
size_t _string_length(const char *str)
{
size_t length = 0;
while (str[length] != '\0')
length++;
return (length);
}
/**
* _string_concatenate - concatenate two strings
*
* @dest: destination string
* @src: source string
* Return: Pointer to the concatenated string.
*/
char *_string_concatenate(const char *dest, const char *src)
{
size_t dest_len = _string_length(dest);
size_t src_len = _string_length(src);
size_t total_len = dest_len + src_len + 1;
char *result = (char *)malloc(total_len * sizeof(char));
if (result == NULL)
return (NULL);
size_t i, j;
for (i = 0; i < dest_len; i++)
result[i] = dest[i];
for (j = 0; j < src_len; j++)
result[i + j] = src[j];
result[i + j] = '\0';
return (result);
}
/**
* _string_copy - copies str to another
* @dest: destination string
* @src: the string that we're going to copy
* Return: Pointer to the destination string.
*/
char *_string_copy(char *dest, const char *src)
{
size_t i = 0;
while (src[i] != '\0')
{
dest[i] = src[i];
i++;
}
dest[i] = '\0';
return (dest);
}
/**
* _string_duplicate - duplicate str and return a pointer to newly allocated str
* @str: pointer to be duplicated.
* Return: Pointer to the duplicated string or NULL if memory allocation fails.
*/
char *_string_duplicate(const char *str)
{
size_t len = _string_length(str) + 1;
char *duplicate = (char *)malloc(len * sizeof(char));
if (duplicate == NULL)
return (NULL);
_string_copy(duplicate, str);
return (duplicate);
}
/**
* _memory_copy - function that copies memory area.
* @dest: destination memory area.
* @src: source memory area.
* @n: number of bytes to be copied.
* Return: Pointer to the destination memory area.
*/
void *_memory_copy(void *dest, const void *src, size_t n)
{
char *d = (char *)dest;
const char *s = (const char *)src;
for (size_t i = 0; i < n; i++)
d[i] = s[i];
return (dest);
}
