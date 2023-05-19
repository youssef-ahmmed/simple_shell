#include "shell.h"

/**
 * handle_all_signals - handle signals
*/
void handle_all_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	signal(SIGTSTP, handle_sigstp);
}

/**
 * handle_sigint - Signal handler for SIGINT (Ctrl+C)
 * @sig: Signal number
 *
 * Return: Nothing
 */
void handle_sigint(int sig)
{
	(void) sig;
	_puts("\n", STDERR_FILENO);
	prompt();
}

/**
 * handle_sigquit - Signal handler for SIGQUIT (Ctrl+\)
 * @sig: Signal number
 *
 * Return: Nothing
 */
void handle_sigquit(int sig)
{
	(void) sig;
	_puts("Quit (core dumped)\n", STDERR_FILENO);
	exit(EXIT_SUCCESS);
}

/**
 * handle_sigstp - Signal handler for SIGTSTP (Ctrl+Z)
 * @sig: Signal number
 *
 * Return: Nothing
 */
void handle_sigstp(int sig)
{
	(void) sig;
	_puts("\n", STDOUT_FILENO);
	prompt();
}
