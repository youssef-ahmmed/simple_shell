#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @str: the string
 * Return: the length
*/

int _strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 * _strcat - concatenates two strings
 * @destination: dest string
 * @source: src string
 * Return: pointer to dest
*/

char *_strcat(char *destination, char *source)
{
	char *result = destination;

	while (*destination)
		destination++;

	while (*source)
		*destination++ = *source++;

	*destination = *source;

	return (result);
}

/**
 * _strcpy - copies a string
 * @destination: the destination
 * @source: the source
 * Return: pointer to destination
*/

char *_strcpy(char *destination, char *source)
{
	int index = 0;

	if (destination == source || source == NULL)
		return (destination);

	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}
	destination[index] = '\0';

	return (destination);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
*/

char *_strdup(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	for (length++; length--;)
		result[length] = *--str;
	return (result);
}
