#include "shell.h"

static char *last_line;

/**
 * get_input_command - get input commands from user
 * Return: parsed command
 */
char *get_input_command(void)
{
	/* Use getline */
	char *line = NULL;
	size_t size = 0;
	ssize_t num_of_chars;

	do {
		prompt();

		num_of_chars = getline(&line, &size, stdin);
		if (num_of_chars == -1)
		{
			free(line);
			_puts("\n", STDOUT_FILENO);
			return (NULL);
		}

		line[num_of_chars - 1] = '\0';
	} while (line[0] == '\0' || isspace(line[0]));

	last_line = line;
	return (line);
}

/**
 * free_last_line - frees last input command typed by the user
 */
void free_last_line(void)
{
	free(last_line);
	last_line = NULL;
}
