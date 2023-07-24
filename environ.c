#include "shell.h"

/**
* print_environment - prints the current environment variables
* @data: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* Return: Always 0
*/
int print_environment(info_t *data)
{
print_list_strings(data->environment);
return (0);
}


/**
* find_env_value - finds the value of an environment variable
* @data: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* @var_name: Name of the environment variable to find.
*
* Return: The value of the environment variable, or NULL if not found.
*/
char *find_env_value(info_t *data, const char *var_name)
{
list_t *env_node = data->environment;
char *value;

while (env_node)
{
value = starts_with(env_node->str, var_name);
if (value && *value)
return (value);
env_node = env_node->next;
}

return (NULL);
}


/**
* initialize_or_modify_env - Initializes a new environment variable
*                            or modifies an existing one.
* @data: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* Return: 0 on success, 1 on failure.
*/
int initialize_or_modify_env(info_t *data)
{
if (data->argc != 3)
{
_eputs("Incorrect number of arguments\n");
return (1);
}

if (update_env_variable(data, data->argv[1], data->argv[2]))
return (0);

return (1);
}


/**
* remove_environment_variable - Remove an environment variable.
* @data: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* Return: Always 0
*/
int remove_environment_variable(info_t *data)
{
int i;

if (data->argc == 1)
{
_eputs("Too few arguments.\n");
return (1);
}

for (i = 1; i < data->argc; i++)
{
unset_env_variable(data, data->argv[i]);
}

return (0);
}

/**
* create_and_populate_env_list - Creat and populates a linked list for env var
* @data: Structure containing potential args maintain const function prototype
* Return: Always 0
*/
int create_and_populate_env_list(info_t *data)
{
list_t *env_list = NULL;
size_t i;

for (i = 0; environ[i]; i++)
{
add_node_end(&env_list, environ[i], 0);
}

data->environment = env_list;
return (0);
}
