#include "shell.h"
#include <stdio.h>

/**
* _myhistory - displays the history list, one command by line, preceded
*              with line numbers, starting at 0.
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
*  Return: Always 0
*/
int _myhistory(info_t *info)
{
int line_number = 0;
list_t *current = info->history;
while (current != NULL)
{
printf("%d %s\n", line_number, current->str);
line_number++;
current = current->next;
}
return (0);
}

/**
* unset_alias - unsets alias to string
* @info: parameter struct
* @str: the string alias
*
* Return: Always 0 on success, 1 on error
*/
int unset_alias(info_t *info, char *str)
{
char *p = _strchr(str, '=');
if (!p)
return (1);
*p = '\0';
int ret = delete_node_with_prefix(&(info->alias), str);
*p = '=';
return (ret);
}

/**
* set_alias - sets alias to string
* @info: parameter struct
* @str: the string alias
*
* Return: Always 0 on success, 1 on error
*/
int set_alias(info_t *info, char *str)
{
char *p = _strchr(str, '=');
if (!p)
return (1);
if (!*(p + 1))
return (unset_alias(info, str));
unset_alias(info, str);
return (add_node_end(&(info->alias), str) == NULL ? 1 : 0);
}

/**
* print_alias - prints an alias string
* @node: the alias node
*
* Return: Always 0 on success, 1 on error
*/
int print_alias(list_t *node)
{
if (node)
{
char *p = _strchr(node->str, '=');
if (p)
{
*p = '\0'; /* Temporarily terminate the string at '=' */
printf("%s='%s'\n", node->str, p + 1);
*p = '='; /* Restore the original string */
return (0);
}
}
return (1);
}

/**
* _myalias - mimics the alias builtin (man alias)
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
*  Return: Always 0
*/
int _myalias(info_t *info)
{
if (info->argc == 1)
{
list_t *node = info->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}

for (int i = 1; info->argv[i]; i++)
{
char *p = _strchr(info->argv[i], '=');
if (p)
{
set_alias(info, info->argv[i]);
}
else
{
list_t *node = node_starts_with(info->alias, info->argv[i], '=');
print_alias(node);
}
}
return (0);
}
