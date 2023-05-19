#include "shell.h"

/**
 * _getenv - gets an environment variable
 * @name: name of environment variable
 * Return: value or NULL
 */
char *_getenv(const char *name)
{
	char **env;
	size_t name_len = strlen(name);

	for (env = environ; *env != NULL; env++)
	{
		if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{
			return (&(*env)[name_len + 1]);
		}
	}

	return (NULL);
}
