#include "shell.h"

/**
 * _puts - prints a string to stdout
 * @str: string to print
 * @fd_flag: standard file descriptor flag
 * 1 for stdout, 2 for stderr
 */
void _puts(char *str, int fd_flag)
{
	size_t str_len = 0;
	ssize_t written_chars = 0;

	str_len = strlen(str);
	written_chars = write(fd_flag, str, str_len);
	if (written_chars == -1)
	{
		perror("Write");
	}
}
