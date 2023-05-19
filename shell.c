#include "shell.h"

/**
 * main - entry point
 * Return: 0
*/
int main(void)
{
	int status;
	char *command = NULL;
	char **argv = NULL;

	/* signal handling */
	handle_all_signals();

	do {
		/* 1. Input command stored in buffer using getline */
		command = get_input_command();
		if (!command || !*command)
			break;

		/* 2. Tokenize the command using strtok */
		argv = get_tokens(command);
		if (!argv || !*argv)
		{
			free(command);
			free_tokens(argv);
			continue;
		}

		/* 3. Execute Command */
		status = execute_commands(argv, command);
		if (status == -1)
			continue;

		free(command);
		free_tokens(argv);

		status = 1;
	} while (status);

	return (EXIT_SUCCESS);
}
