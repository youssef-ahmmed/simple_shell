#include "shell.h"

/**
 * free_args - frees arguments
 * @argv: arguments
 * @count: number of arguments
*/
void free_args(char **argv, int count)
{
	int i;

	for (i = 0; i < count; i++)
		free(argv[i]);
	free(argv);
	exit(EXIT_FAILURE);
}

/**
 * free_tokens - frees tokens
 * @token: tokens
*/
void free_tokens(char **token)
{
	int i;

	for (i = 0; token[i]; i++)
		free((token[i]));

	free(token);
}
