#include "shell.h"

/**
 * pointer_free - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 * Return: 1 if freed, otherwise 0.
*/

int pointer_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * string_free - frees a string of strings
 * @ptr: list of strings
*/

void string_free(char **ptr)
{
	char **list = ptr;

	if (!ptr)
		return;
	while (*ptr)
		free(*ptr++);
	free(list);
}

/**
 * _memset - fills a block of memory with a constant byte
 * @str: the pointer to the memory area
 * @value: the byte to fill *str with
 * @num: the amount of bytes to be filled
 * Return: (str) a pointer to the memory area
*/
char *_memset(char *str, char value, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		str[i] = value;
	return (str);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous allocated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 * Return: pointer to new block
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_address;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	new_address = malloc(new_size);
	if (!new_address)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_address[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_address);
}
