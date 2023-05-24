#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @cstr: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *cstr)
{
	int x = 0;
	unsigned long int result = 0;

	if (*cstr == '+')
		cstr++;  /* TODO: why does this make main return 255? */
	for (x = 0;  cstr[x] != '\0'; x++)
	{
		if (cstr[x] >= '0' && cstr[x] <= '9')
		{
			result *= 10;
			result += (cstr[x] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @prminfo: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *prminfo, char *estr)
{
	_eputs(prminfo->fname);
	_eputs(": ");
	print_d(prminfo->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(prminfo->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int x, total = 0;
	unsigned int abs, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		abs = -input;
		__putchar('-');
		total++;
	}
	else
		abs = input;
	current = abs;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (abs / x)
		{
			__putchar('0' + current / x);
			total++;
		}
		current %= x;
	}
	__putchar('0' + current);
	total++;

	return (total);
}

/**
 * convert_number - converter function, a clone of itoa
 * @no: number
 * @b: base
 * @arflags: argument flags
 *
 * Return: string
 */
char *convert_number(long int no, int b, int arflags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = no;

	if (!(arflags & CONVERT_UNSIGNED) && no < 0)
	{
		n = -no;
		sign = '-';

	}
	array = arflags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % b];
		n /= b;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @adstrm: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *adstrm)
{
	int x;

	for (x = 0; adstrm[x] != '\0'; x++)
		if (adstrm[x] == '#' && (!x || adstrm[x - 1] == ' '))
		{
			adstrm[x] = '\0';
			break;
		}
}
