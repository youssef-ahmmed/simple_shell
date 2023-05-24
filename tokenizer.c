#include "shell.h"

/**
 * split_string - splits a string into words
 * @str: string to split
 * @delimiter: delimiter
 * Return: NULL on error
 */
char **split_string(char *str, char *delimiter)
{
	int i, j, k, m;
	int words_count = count_words(str, delimiter);
	char **tokenized_str;

	if (words_count == 0)
		return (NULL);

	if (str == NULL || str[0] == 0)
		return (NULL);

	if (!delimiter)
		delimiter = " ";

	tokenized_str = malloc((1 + words_count) * sizeof(char *));
	if (!tokenized_str)
		return (NULL);
	for (i = 0, j = 0; j < words_count; j++)
	{
		while (is_delim(str[i], delimiter))
			i++;
		k = 0;
		while (!is_delim(str[i + k], delimiter) && str[i + k])
			k++;
		tokenized_str[j] = malloc((k + 1) * sizeof(char));
		if (!tokenized_str[j])
		{
			for (k = 0; k < j; k++)
				free(tokenized_str[k]);
			free(tokenized_str);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			tokenized_str[j][m] = str[i++];
		tokenized_str[j][m] = 0;
	}
	tokenized_str[j] = NULL;
	return (tokenized_str);
}

/**
 * count_words - counts the number of words in a string
 * @str: string to count
 * @delimiter: delimiter
 * Return: number of words
 */
int count_words(char *str, char *delimiter)
{
	int i, words_count = 0;

	if (str == NULL || str[0] == 0)
		return (0);

	if (delimiter == NULL)
		delimiter = " ";

	for (i = 0; str[i] != '\0'; i++)
	{
		if (!is_delim(str[i], delimiter) &&
			(is_delim(str[i + 1], delimiter) || !str[i + 1]))
			words_count++;
	}

	return (words_count);
}
