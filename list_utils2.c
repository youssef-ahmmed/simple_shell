#include "shell.h"

/**
 * list_len - returns the length of a list
 * @node: pointer to first node
 * Return: length of list
*/

size_t list_len(const list_t *node)
{
	size_t i = 0;

	while (node)
	{
		node = node->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 * Return: array of strings
*/

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **str_arr;
	char *str;

	if (!head || !i)
		return (NULL);
	str_arr = malloc(sizeof(char *) * (i + 1));
	if (!str_arr)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(str_arr[j]);
			free(str_arr);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		str_arr[i] = str;
	}
	str_arr[i] = NULL;
	return (str_arr);
}

/**
 * print_list_str - prints all elements of a list_t linked list
 * @node: pointer to first node
 * Return: i number of elements
*/

size_t print_list_str(const list_t *node)
{
	size_t i = 0;

	while (node)
	{
		_puts(node->str ? node->str : "(nil)");
		_puts("\n");
		node = node->next;
		i++;
	}
	return (i);
}

/**
 * free_list - frees a list
 * @head_ptr: pointer to first node
*/

void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
