#include "shell.h"

/**
 * get_path - get the path of the shell
 * Return: the path
 */
char *get_path(void)
{
	return (_getenv("PATH"));
}

/**
 * find_file_in_path - search for a command in path
 * @command: command to search
 * Return: pointer to the executable file found
 */
char *find_file_in_path(char *command)
{
	struct stat st;
	int ret_stat, i;
	char full_path[MAX_PATH_LENGTH], *path_var, *found_dir, **directory;

	path_var = get_path();
	if (path_var == NULL)
		return (NULL);

	directory = tokenizer(path_var, PATH_SEPARATOR);
	if (directory == NULL)
		return (NULL);

	for (i = 0; directory[i]; i++)
	{
		memset(full_path, 0, MAX_PATH_LENGTH);
		strcpy(full_path, directory[i]);
		strcat(full_path, "/");
		strcat(full_path, command);
		strcat(full_path, "\0");
		ret_stat = stat(full_path, &st);
		if (ret_stat == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
		{
			free_tokens(directory);
			found_dir = malloc(sizeof(char) * strlen(full_path) + 1);
			if (found_dir == NULL)
				return (NULL);
			strcpy(found_dir, full_path);
			return (found_dir);
		}
	}
	if (ret_stat == -1)
		free_tokens(directory);

	return (NULL);
}
