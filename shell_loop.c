#include "shell.h"

/**
 * shell_exec - executes a command
 * @info: the parameter & return info struct
 * @argv: the command
 * Return: builtin_ret
*/
int shell_exec(info_t *info, char **argv)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		reset_info(info);
		if (interactive(info))
			_puts("$ ");
		print_char(BUFFER_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			initialize_info(info, argv);
			builtin_ret = find_builtin_command(info);
			if (builtin_ret == -1)
				find_command(info);
		}
		else if (interactive(info))
			_putchar('\n');
		deallocate_info(info, 0);
	}
	deallocate_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->error_num == -1)
			exit(info->status);
		exit(info->error_num);
	}
	return (builtin_ret);
}

/**
 * fork_command - finds a command in PATH
 * @info: the parameter & return info struct
*/
void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			deallocate_info(info, 1);
			if (errno == EACCES)
				exit(PERMISSION_DENIED);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == PERMISSION_DENIED)
				print_error(info, "Permission denied\n");
		}
	}
}
