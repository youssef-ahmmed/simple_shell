#include "shell.h"

/**
 * _strlen - calculates the length of a string
 * @str: string
 * Return: length of string
 */
size_t _strlen(const char *str)
{
	size_t count = 0, i = 0;

	if (str == NULL)
		return (0);

	while (str[i] != '\0')
	{
		count++;
		i++;
	}

	return (count);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 * Return: 0 if equal
 * otherwise -1
 */
int _strcmp(const char *s1, const char *s2)
{
	return (strcmp(s1, s2));
}

/**
 * _atoi - Converts a string to an integer.
 * @str: The string to convert.
 *
 * Return: The integer value of the string.
 */
unsigned int _atoi(const char *str)
{
	int i, sign;
	unsigned int number;

	i = 0;
	sign = 1;
	number = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '-')
			sign *= -1;
		else if ('0' <= str[i] && str[i] <= '9')
			number = number * 10 + (str[i] - '0');
		else
			break;
		i++;
	}

	return (number * sign);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}
