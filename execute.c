#include "shell.h"

/**
 * execute_commands - execute builtin and external commands
 * @argv: arguments
 * @command: all command after getline
 * Return: 1 if command executed, 0 if not
 */
int execute_commands(char **argv, char *command)
{
	pid_t pid;
	int status = 0;
	char *command_path, *env_var[2];

	UNUSED(command);
	if (argv == NULL || *argv == NULL)
		return (status);

	status = check_for_builtin(argv);
	if (status != 0)
		return (status);

	pid = fork();
	if (pid == -1)
		exit_error(argv);

	if (pid == 0)
	{
		env_var[0] = get_path();
		env_var[1] = NULL;
		command_path = NULL;
		if (argv[0][0] != '/')
			command_path = find_file_in_path(argv[0]);
		else if (command_path == NULL)
			command_path = argv[0];
		if (execve(command_path, argv, env_var) == -1)
		{
			exit_error(argv);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (status == 0);
}

/**
 * exit_error - exit when error
 * @argv: tokenized args
*/
void exit_error(char **argv)
{
	perror(argv[0]);
	free_tokens(argv);
	free_last_line();
}
