#include "shell.h"

/**
 * _strchr - locates a character in a string
 * @str: string to search
 * @c: character to search for
 * Return: A pointer to the char
*/

char *_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

/**
 * _strncat - concatenates two strings
 * @dest: destination string
 * @src: source string
 * @num: number of characters
 * Return: pointer to destination
*/

char *_strncat(char *dest, char *src, int num)
{
	int i, j;
	char *str = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < num)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < num)
		dest[i] = '\0';
	return (str);
}

/**
 * _strncpy - copies a string
 * @dest: the destination
 * @src: the source
 * @num: number of characters
 * Return: pointer to destination
*/

char *_strncpy(char *dest, char *src, int num)
{
	int i, j;
	char *str = dest;

	i = 0;
	while (src[i] != '\0' && i < num - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < num)
	{
		j = i;
		while (j < num)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (str);
}

/**
 * _strcmp - compares two strings
 * @str1: first string
 * @str2: second string
 * Return: 0 if equal, -1 if str1 < str2, 1 if str1 > str2
*/

int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}
