#include "shell.h"

/**
 * find_command - finds a command in PATH
 * @info: the parameter & return info struct
*/
void find_command(info_t *info)
{
	char *path = NULL;
	int index, k;

	info->path = info->argv[0];
	if (info->line_count_flag == 1)
	{
		info->line_count++;
		info->line_count_flag = 0;
	}
	for (index = 0, k = 0; info->arg[index]; index++)
		if (!is_delim(info->arg[index], " \t\n"))
			k++;
	if (!k)
		return;

	path = search_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = COMMAND_NOT_FOUND;
			print_error(info, "not found\n");
		}
	}
}

/**
 * find_builtin_command - finds a builtin command
 * @info: the parameter & return info struct
 * Return: builtin_ret
*/

int find_builtin_command(info_t *info)
{
	int index, builtin_ret = -1;

	builtin_table builtin_list[] = {
		{"exit", shell_exit},
		{"env", shell_env},
		{"setenv", shell_setenv},
		{"unsetenv", shell_unsetenv},
		{"cd", shell_cd},
		{"alias", shell_alias},
		{NULL, NULL}};

	for (index = 0; builtin_list[index].type; index++)
		if (_strcmp(info->argv[0], builtin_list[index].type) == 0)
		{
			info->line_count++;
			builtin_ret = builtin_list[index].func(info);
			break;
		}
	return (builtin_ret);
}
