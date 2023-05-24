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


#define BUFFER_FLUSH (-1)

#define NORMAL_COMMAND 0
#define LOGICAL_OR_COMMAND 1
#define LOGICAL_AND_COMMAND 2
#define SEQUENTIAL_COMMAND 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024

#define PERMISSION_DENIED 126
#define COMMAND_NOT_FOUND 127

#ifndef S_IFREG
#define S_IFREG 0100000
#endif

extern char **environ;

/**
 * struct list_str - list of strings
 * @num: the list number
 * @str: the string
 * @next: the next node
 */
typedef struct list_str
{
	int num;
	char *str;
	struct list_str *next;
} list_t;

/**
 * struct parsed_info - Structure for passing information to functions
 * @arg: Command argument
 * @argv: Command argument vector
 * @path: Path
 * @line_count: Line count
 * @error_num: Error number
 * @env_changed: Flag indicating if the environment has changed
 * @status: Status
 * @command_buffer: Command buffer
 * @command_buffer_type: Type of command buffer
 * @file_name: File name
 * @env: Environment
 * @alias: Alias
 * @environ: Environment
 * @argc: Argument count
 * @line_count_flag: Line count flag
 * @file_descriptor: File descriptor
 */
typedef struct parsed_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int error_num;
	int line_count_flag;
	char *file_name;
	list_t *env;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **command_buffer;
	int command_buffer_type;
	int file_descriptor;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0}

/**
 * struct builtin - function selects suitable builtin function
 * @type: type of builtin
 * @func: selected builtin function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int check_non_interactive(int argc, char **argv, info_t info[]);

int find_builtin_command(info_t *);
void find_command(info_t *);
void fork_command(info_t *);
int shell_exec(info_t *, char **);

/* path handling */
int is_cmd(info_t *, char *);
char *dup_chars(const char *, int, int);
char *search_path(info_t *, char *, char *);

/* printing functions */
void print_string(char *);
int print_char(char);

/* string overwritten functions */
int _strlen(char *);
int _strcmp(char *, char *);
char *find_prefix(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* string tokenization functions */
char **split_string(char *, char *);
int count_words(char *str, char *delimiter);

/* memory functions */
char *_memset(char *, char, unsigned int);
void string_free(char **);
void *_realloc(void *, unsigned int, unsigned int);
int pointer_free(void **);

/* validation functions */
int interactive(info_t *);
int is_delim(char, char *);

int parse_error_integer(char *);
void print_error(info_t *, char *);
int print_decimal(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

int shell_exit(info_t *);
int shell_cd(info_t *);

int shell_alias(info_t *);

ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
ssize_t input_buffer(info_t *, char **, size_t *);
ssize_t read_buffer(info_t *, char *, size_t *);
void handle_sigint_signal(int);

void reset_info(info_t *);
void initialize_info(info_t *, char **);
void deallocate_info(info_t *, int);

/* environment functions */
char *_getenv(info_t *, const char *);
int shell_env(info_t *);
int shell_setenv(info_t *);
int shell_unsetenv(info_t *);
int init_env_variables(info_t *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* liked list functions */
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* alias functions */
int detect_command_separator(info_t *, char *, size_t *);
void handle_sep(info_t *, char *, size_t *, size_t, size_t);
int alias_replace(info_t *);
int variables_substitute(info_t *);
int string_replace(char **, char *);
int unset_alias(info_t *, char *);
int print_alias(list_t *);

#endif
