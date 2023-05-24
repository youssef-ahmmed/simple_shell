#include "shell.h"

/**
 * get_input - reads input from stdin
 * @info: pointer to info struct
 * Return: number of bytes read || -1
 */

ssize_t get_input(info_t *info)
{
	static char *input_buf;
	static size_t i, j, len;
	ssize_t read_result = 0;
	char **arg_ptr = &(info->arg), *current_char_ptr;

	_putchar(BUFFER_FLUSH);
	read_result = input_buffer(info, &input_buf, &len);

	if (read_result == -1)
		return (-1);

	if (len)
	{
		j = i;
		current_char_ptr = input_buf + i;

		handle_sep(info, input_buf, &j, i, len);

		while (j < len)
		{
			if (detect_command_separator(info, input_buf, &j))
				break;
			j++;
		}

		i = j + 1;

		if (i >= len)
		{
			i = len = 0;
			info->command_buffer_type = NORMAL_COMMAND;
		}
		*arg_ptr = current_char_ptr;

		return (_strlen(current_char_ptr));
	}
	*arg_ptr = input_buf;

	return (read_result);
}

/**
 * _getline - reads input from stdin
 * @info: pointer to info struct
 * @line_ptr: pointer to char buffer
 * @line_len: pointer to length
 * Return: number of bytes read || -1
 */

int _getline(info_t *info, char **line_ptr, size_t *line_len)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t buffer_pos, buffer_len;
	size_t k;
	ssize_t read_result = 0, s = 0;
	char *line = NULL, *new_line = NULL, *c;

	line = *line_ptr;
	if (line && line_len)
		s = *line_len;
	if (buffer_pos == buffer_len)
		buffer_pos = buffer_len = 0;

	read_result = read_buffer(info, buffer, &buffer_len);
	if (read_result == -1 || (read_result == 0 && buffer_len == 0))
		return (-1);

	c = _strchr(buffer + buffer_pos, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : buffer_len;
	new_line = _realloc(line, s, s ? s + k : k + 1);
	if (!new_line)
		return (line ? free(line), -1 : -1);

	if (s)
		_strncat(new_line, buffer + buffer_pos, k - buffer_pos);
	else
		_strncpy(new_line, buffer + buffer_pos, k - buffer_pos + 1);

	s += k - buffer_pos;
	buffer_pos = k;
	line = new_line;

	if (line_len)
		*line_len = s;
	*line_ptr = line;
	return (s);
}

/**
 * read_buffer - reads input from stdin
 * @info: pointer to info struct
 * @read_buffer: pointer to char buffer
 * @read_pos: pointer to length
 * Return: number of bytes read || -1
 */

ssize_t read_buffer(info_t *info, char *read_buffer, size_t *read_pos)
{
	ssize_t read_result = 0;

	if (*read_pos)
		return (0);
	read_result = read(info->file_descriptor, read_buffer, READ_BUFFER_SIZE);
	if (read_result >= 0)
		*read_pos = read_result;
	return (read_result);
}

/**
 * input_buffer - reads input from stdin
 * @info: pointer to info struct
 * @buffer: pointer to char buffer
 * @len: pointer to length
 * Return: number of bytes read || -1
 */

ssize_t input_buffer(info_t *info, char **buffer, size_t *len)
{
	ssize_t r = 0;
	size_t input_len_p = 0;

	if (!*len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_sigint_signal);
		r = _getline(info, buffer, &input_len_p);
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->line_count_flag = 1;
			remove_comments(*buffer);
			{
				*len = r;
				info->command_buffer = buffer;
			}
		}
	}
	return (r);
}

/**
 * handle_sigint_signal - handles SIGINT
 * @sig_num: signal
 */

void handle_sigint_signal(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}
