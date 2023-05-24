#include "shell.h"

/**
 * initialize_info - initialize info struct
 * @info: info struct address
 * @av: argument vector from main()
*/
void initialize_info(info_t *info, char **av)
{
	int i = 0;

	info->file_name = av[0];
	if (info->arg)
	{
		info->argv = split_string(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		alias_replace(info);
		variables_substitute(info);
	}
}

/**
 * reset_info - reset info struct fields
 * @info: info struct address
*/
void reset_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * deallocate_info - frees info struct fields
 * @info: info struct address
 * @all: true if freeing all fields
*/
void deallocate_info(info_t *info, int all)
{
	string_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->command_buffer)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->alias)
			free_list(&(info->alias));
		string_free(info->environ);
			info->environ = NULL;
		pointer_free((void **)info->command_buffer);
		if (info->file_descriptor > 2)
			close(info->file_descriptor);
		_putchar(BUFFER_FLUSH);
	}
}
