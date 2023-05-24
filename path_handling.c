#include "shell.h"

/**
 * search_path - searches for a command in a list of paths
 * @info: pointer to info_t struct
 * @path_list: list of paths
 * @command: command to search
 * Return: command || new_path || NULL on error
*/
char *search_path(info_t *info, char *path_list, char *command)
{
	int index = 0, start_pos = 0;
	char *new_path;

	if (!path_list)
		return (NULL);
	if ((_strlen(command) > 2) && find_prefix(command, "./"))
	{
		if (is_cmd(info, command))
			return (command);
	}
	while (1)
	{
		if (!path_list[index] || path_list[index] == ':')
		{
			new_path = dup_chars(path_list, start_pos, index);
			if (!*new_path)
				_strcat(new_path, command);
			else
			{
				_strcat(new_path, "/");
				_strcat(new_path, command);
			}
			if (is_cmd(info, new_path))
				return (new_path);
			if (!path_list[index])
				break;
			start_pos = index;
		}
		index++;
	}
	return (NULL);
}

/**
 * is_cmd - function to check if a file is a command
 * @info: pointer to info_t struct
 * @path: path to check
 * Return: 0 || 1
*/

int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;

	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates a string
 * @path: string to duplicate
 * @start: start index
 * @stop: stop index
 * Return: pointer to new string
*/

char *dup_chars(const char *path, int start, int stop)
{
	static char buffer[1024];
	int index, j;

	for (j = 0, index = start; index < stop; index++)
		if (path[index] != ':')
			buffer[j++] = path[index];
	buffer[j] = 0;
	return (buffer);
}
