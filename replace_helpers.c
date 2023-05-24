#include "shell.h"

/**
 * string_replace - replaces a string
 * @old_string: the old string
 * @new_string: the new string
 * Return: 1 if replaced
 */

int string_replace(char **old_string, char *new_string)
{
	free(*old_string);
	*old_string = new_string;
	return (1);
}

/**
 * variables_substitute - replaces vars in the tokenized string
 * @info: the parameter struct
 * Return: 0
 */

int variables_substitute(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			string_replace(&(info->argv[i]),
						   _strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			string_replace(&(info->argv[i]),
						   _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			string_replace(&(info->argv[i]),
						   _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		string_replace(&info->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * alias_replace - replaces alias
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */

int alias_replace(info_t *info)
{
	int i;
	list_t *node;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * detect_command_separator - detects command separator
 * @info: the parameter struct
 * @buf: the buffer
 * @ptr: the pointer
 * Return: 1 if replaced, 0 otherwise
 */

int detect_command_separator(info_t *info, char *buf, size_t *ptr)
{
	size_t j = *ptr;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->command_buffer_type = LOGICAL_OR_COMMAND;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->command_buffer_type = LOGICAL_AND_COMMAND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->command_buffer_type = SEQUENTIAL_COMMAND;
	}
	else
		return (0);
	*ptr = j;
	return (1);
}

/**
 * handle_sep - handles command separator
 * @info: the parameter struct
 * @buf: the buffer
 * @ptr: the pointer
 * @i: the index
 * @len: the length
 */

void handle_sep(info_t *info, char *buf, size_t *ptr, size_t i, size_t len)
{
	size_t j = *ptr;

	if (info->command_buffer_type == LOGICAL_AND_COMMAND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->command_buffer_type == LOGICAL_OR_COMMAND)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*ptr = j;
}
