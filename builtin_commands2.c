#include "shell.h"

/**
 * shell_setenv - sets an environment variable
 * @args: arguments
 * Return: 1 if succeeded, -1 if error
 */
int shell_setenv(char **args)
{
	char *VAR, *VALUE;

	if (args[1] == NULL || args[2] == NULL)
	{
		_puts("Usage: setenv VARIABLE VALUE\n", STDERR_FILENO);
		return (ERROR_IN_EXECUTION);
	}

	VAR = args[1];
	VALUE = args[2];

	if (setenv(VAR, VALUE, 1) != 0)
	{
		_puts("setenv", STDERR_FILENO);
		return (ERROR_IN_EXECUTION);
	}

	return (EXECUTE_SUCCESSFULLY);
}

/**
 * shell_unsetenv - unset an environment variable
 * @args: argument
 * Return: 1 if succeeded, -1 if error
 */
int shell_unsetenv(char **args)
{
	char *VAR;

	if (args[1] == NULL)
	{
		_puts("Usage: unsetenv VARIABLE\n", STDERR_FILENO);
		return (ERROR_IN_EXECUTION);
	}

	VAR = args[1];

	if (unsetenv(VAR) == -1)
	{
		_puts("unsetenv", STDERR_FILENO);
		return (ERROR_IN_EXECUTION);
	}

	return (EXECUTE_SUCCESSFULLY);
}

/**
 * shell_clear - clears the entire screen
 * @args: arguments
 * Return: 1 if succeeded, -1 if error
 */
int shell_clear(char **args)
{
	UNUSED(args);
	_puts("\033[2J\033[H", STDOUT_FILENO);

	return (EXECUTE_SUCCESSFULLY);
}
