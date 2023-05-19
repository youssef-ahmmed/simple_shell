#include "shell.h"

/**
 * str_token - splits a string into tokens
 * @str: string to be splited
 * @delim: delimiter
 * Return: token
 */
char *str_token(char *str, const char *delim)
{
	static char *next_token;
	char *token_start;
	char *token_end;

	if (str != NULL)
	{
		next_token = str;
	}
	else if (next_token == NULL)
	{
		return (NULL);
	}

	token_start = next_token;
	token_end = strpbrk(next_token, delim);

	if (token_end != NULL)
	{
		*token_end = '\0';
		next_token = token_end + 1;
	}
	else
	{
		next_token = NULL;
	}

	return (token_start);
}

/**
 * tokenizer - splits a string into tokens
 * @str: string to be splited
 * @delim: delimiter
 * Return: token
 */
char **tokenizer(char *str, const char *delim)
{
	char *token = NULL;
	char **tokenized_str = NULL;
	int idx = 0;
	int arg_numbers;

	arg_numbers = count_args(str, delim);
	tokenized_str = malloc(sizeof(char *) * (arg_numbers + 1));
	if (tokenized_str == NULL)
		return (NULL);

	token = str_token(str, delim);
	while (token != NULL)
	{
		tokenized_str[idx] = malloc(strlen(token) + 1);
		if (tokenized_str[idx] == NULL)
		{
			free_args(tokenized_str, arg_numbers);
		}

		strcpy(tokenized_str[idx], token);
		token = str_token(NULL, delim);
		idx++;
	}

	tokenized_str[idx] = NULL;
	return (tokenized_str);
}

/**
 * count_args - counts the number of arguments
 * @str: string
 * @delim: delimiter
 * Return: number of arguments
 */
int count_args(char *str, const char *delim)
{
	char *copy = _strdup(str);
	char *token;
	int count = 0;

	if (!str || !*str)
		return (0);

	token = str_token(copy, delim);
	while (token != NULL)
	{
		token = str_token(NULL, delim);
		count++;
	}
	free(copy);

	return (count);
}

/**
 * get_tokens - splits a string into tokens
 * @str: string
 * Return: tokens
 */
char **get_tokens(char *str)
{
	char **tokens = NULL;
	char *temp = NULL;

	temp = _strdup(str);
	if (temp == NULL)
	{
		_puts("Memory Allocation Error", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}

	tokens = tokenizer(temp, COMMAND_SEPARATOR);
	free(temp);

	return (tokens);
}
