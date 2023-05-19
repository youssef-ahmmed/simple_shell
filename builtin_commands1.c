#include "shell.h"

/**
 * change_directory - changes the current working directory
 * @directory: directory to be changed
 * Return: 1 if succeeded, -1 if error
 */
int change_directory(char *directory)
{
	char cwd[256];
	int changed_dir;

	changed_dir = chdir(directory);
	if (changed_dir == -1)
	{
		_puts("cd", STDERR_FILENO);
		perror("");
		return (ERROR_IN_EXECUTION);
	}

	if (!getcwd(cwd, sizeof(cwd)))
	{
		_puts("cd: Failed to get current directory\n", STDERR_FILENO);
		return (ERROR_IN_EXECUTION);
	}

	if (setenv("PWD", cwd, 1) != 0)
	{
		_puts("cd: Failed to update PWD environment variable\n", STDERR_FILENO);
		return (ERROR_IN_EXECUTION);
	}

	return (EXECUTE_SUCCESSFULLY);
}

/**
 * shell_cd - changes the current working directory
 * @args: arguments
 * Return: 1 if succeeded, -1 if error
 */
int shell_cd(char **args)
{
	char *directory = args[1], *old_pwd = getenv("OLDPWD");

	if (directory == NULL || strcmp(directory, "~") == 0)
	{
		directory = getenv("HOME");
		if (directory == NULL)
		{
			_puts("cd: No HOME directory found\n", STDERR_FILENO);
			return (ERROR_IN_EXECUTION);
		}
	}
	else if (strcmp(directory, "-") == 0)
	{
		if (old_pwd == NULL)
		{
			_puts("cd: OLDPWD not set\n", STDERR_FILENO);
			return (ERROR_IN_EXECUTION);
		}
		directory = old_pwd;
	}

	if (change_directory(directory) == ERROR_IN_EXECUTION)
		return (ERROR_IN_EXECUTION);

	if (setenv("OLDPWD", old_pwd, 1) != 0)
	{
		_puts("cd: Failed to update OLDPWD environment variable\n", STDERR_FILENO);
		return (ERROR_IN_EXECUTION);
	}

	return (EXECUTE_SUCCESSFULLY);
}


/**
 * shell_env - sets an environment variable
 * @args: arguments
 * Return: 1 if succeeded, -1 if error
 */
int shell_env(char **args)
{
	int i;

	UNUSED(args);

	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i], STDOUT_FILENO);
		_puts("\n", STDOUT_FILENO);
	}

	return (EXECUTE_SUCCESSFULLY);
}

/**
 * shell_help - displays this help information
 * @args: arguments
 * Return: 1 if succeeded, -1 if error
 */
int shell_help(char **args)
{
	UNUSED(args);

	_puts("\nShell Version 1.0.0\n\n", STDOUT_FILENO);
	_puts("Usage: ./hsh\n\n", STDOUT_FILENO);
	_puts("Shell built-in commands:\n\n", STDOUT_FILENO);
	_puts("help\t\tDisplay this help information\n\n", STDOUT_FILENO);
	_puts("cd [dir]\tChange the current working directory\n\n", STDOUT_FILENO);
	_puts("env\t\tDisplay the environment variables\n\n", STDOUT_FILENO);
	_puts("setenv\t\tSet an environment variable\n\n", STDOUT_FILENO);
	_puts("unsetenv\tUnset an environment variable\n\n", STDOUT_FILENO);
	_puts("exit\t\tExit the shell\n\n", STDOUT_FILENO);

	return (EXECUTE_SUCCESSFULLY);
}

/**
 * shell_exit - exits the shell
 * @args: arguments
 * Return: 1 if succeeded, -1 if error
 */
int shell_exit(char **args)
{
	int status = 0;

	if (args[1] != NULL)
	{
		status = _atoi(args[1]);
	}

	free_tokens(args);
	free_last_line();
	exit(status);
}
