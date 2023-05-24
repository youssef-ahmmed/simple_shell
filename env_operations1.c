#include "shell.h"

/**
 * _getenv - Gets the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Name of the environment variable.
 * Return: environment variable value
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = find_prefix(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * shell_env - Prints the current environment.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */

int shell_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * init_env_variables - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */

int init_env_variables(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}


/**
 * shell_setenv - Initialize a new environment variable,
 * @info: Structure containing arguments,
 * Return: Always 0.
 */

int shell_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		print_string("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}


/**
 * shell_unsetenv - Removes an environment variable.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */

int shell_unsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		print_string("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}
