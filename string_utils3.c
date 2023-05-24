#include "shell.h"

/**
 * find_prefix - finds a prefix in a string
 * @haystack: the string
 * @prefix: the prefix
 * Return: A pointer to the prefix
 */

char *find_prefix(const char *haystack, const char *prefix)
{
	while (*prefix)
	{
		if (*prefix++ != *haystack++)
			return (NULL);
	}
	return ((char *)haystack);
}

/**
 * _putchar - writes the character c to stdout
 * @c: the character
 * Return: 1
 */

int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 */

void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}
