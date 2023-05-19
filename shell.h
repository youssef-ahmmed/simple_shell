#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <ctype.h>

#define PROMPT "$ "
#define UNUSED(x) (void)(x)
#define ERROR_IN_EXECUTION (-1)
#define EXECUTE_SUCCESSFULLY (1)
#define PATH_SEPARATOR ":"
#define COMMAND_SEPARATOR " \t\r\n\a"
#define MAX_PATH_LENGTH 1024

extern char **environ;

/**
 * struct builtin - struct for builtin commands
 * @command: command
 * @function: function to be executed
 */
typedef struct builtin
{
	char *command;
	int (*function)(char **args);
} builtin_t;

/**
 * struct special_char - struct for special char in commands
 * @spec_ch: special character
 * @function: to be executed
 */
typedef struct special_char
{
	char *spec_ch;
	int (*function)(char *command);
} special_char_t;

/* get_inputs module */
char *get_input_command(void);
void free_last_line(void);

/* print_prompt module */
void prompt(void);

/* execute module */
int execute_commands(char **argv, char *command);
void exit_error(char **argv);

/* printing to stdout module */
void _puts(char *str, int fd_flag);

/* builtin_commands modules */
int check_for_builtin(char **args);
int change_directory(char *directory);
int shell_cd(char **args);
int shell_env(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_setenv(char **args);
int shell_unsetenv(char **args);
int shell_clear(char **args);

/* special commands modules */
int current_process_id(char *command);
int exit_status(char *command);
int variable_replacement(char *command);
int remove_comment(char *command);
int logical_or(char *command);
int logical_and(char *command);
int command_separator(char *command);

/* helpful methods module */
size_t _strlen(const char *str);
int _strcmp(const char *s1, const char *s2);
unsigned int _atoi(const char *str);
char *_strdup(const char *str);


/* tokenization module */
char *str_token(char *str, const char *delim);
char **tokenizer(char *str, const char *delim);
int count_args(char *str, const char *delim);
char **get_tokens(char *str);

/* free module */
void free_args(char **argv, int count);
void free_tokens(char **token);

/* environment_variable modules */
char *_getenv(const char *name);

/* path module */
char *get_path(void);
char *find_file_in_path(char *command);

/* signal_handler module */
void handle_all_signals();
void handle_sigint(int sig);
void handle_sigquit(int sig);
void handle_sigstp(int sig);

#endif
