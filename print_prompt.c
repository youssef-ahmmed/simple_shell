#include "shell.h"

/**
 * prompt - prints a prompt
 */
void prompt(void)
{
	_puts(PROMPT, STDOUT_FILENO);
	fflush(stdout);
}
