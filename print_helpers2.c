#include "shell.h"

/**
 * convert_number - converts a number to a string
 * @num: the number to be converted
 * @base: the base of the number
 * @flags: flags
 * Return: string
*/

char *convert_number(long int num, int base, int flags)
{
	static char *arr;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long number = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		number = -num;
		sign = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[number % base];
		number /= base;
	} while (number != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * parse_error_integer - parses an integer
 * @str: the string to be parsed
 * Return: 0 || converted number
*/

int parse_error_integer(char *str)
{
	int i;
	int result = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_decimal - prints a decimal
 * @input: the number to be printed
 * @fd: file descriptor
 * Return: number of printed characters
*/

int print_decimal(int input, int fd)
{
	int (*_putchar)(char) = _putchar;
	int i, num = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		_putchar = print_char;
	if (input < 0)
	{
		_abs_ = -input;
		_putchar('-');
		num++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			_putchar('0' + current / i);
			num++;
		}
		current %= i;
	}
	_putchar('0' + current);
	num++;

	return (num);
}

/**
 * print_error - prints an error
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 || converted number
*/

void print_error(info_t *info, char *estr)
{
	print_string(info->file_name);
	print_string(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	print_string(": ");
	print_string(info->argv[0]);
	print_string(": ");
	print_string(estr);
}

/**
 * remove_comments - removes comments from a string
 * @buf: string
*/

void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
