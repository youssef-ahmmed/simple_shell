#include "shell.h"

/**
 * check_for_builtin - executes builtin commands
 * @args: arguments
 * Return: 0 if not found, 1 if executed, -1 if failed
 */
int check_for_builtin(char **args)
{
	int i, builtin_exist = 0;

	builtin_t builtins[] = {
		{"exit", shell_exit},
		{"env", shell_env},
		{"setenv", shell_setenv},
		{"unsetenv", shell_unsetenv},
		{"help", shell_help},
		{"cd", shell_cd},
		{"clear", shell_clear},
		{NULL, NULL}
	};

	if (!args[0])
		return (0);

	i = 0;
	while (builtins[i].command != NULL)
	{
		if (_strcmp(args[0], builtins[i].command) == 0)
		{
			builtin_exist = builtins[i].function(args);
			break;
		}
		i++;
	}

	return (builtin_exist);
}
