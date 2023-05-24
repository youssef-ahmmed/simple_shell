#include "shell.h"

/**
 * interactive - checks if the shell is interactive
 * @info: pointer to info struct
 * Return: 1 || 0
*/
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->file_descriptor <= 2);
}

/**
 * is_delim - checks if character is a delimiter
 * @c: the char to check
 * @delim: delimiter string to check
 * Return: 1 || 0
*/
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
