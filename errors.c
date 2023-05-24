#include "shell.h"

/**
 *_eputs - prints an input string
 * @sttring: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *sttring)
{
	int v = 0;

	if (!sttring)
		return;
	while (sttring[v] != '\0')
	{
		_eputchar(sttring[v]);
		v++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @y: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char y)
{
	static int v;
	static char buf[WRITE_BUF_SIZE];

	if (y == BUF_FLUSH || v >= WRITE_BUF_SIZE)
	{
		write(2, buf, v);
		v = 0;
	}
	if (y != BUF_FLUSH)
		buf[v++] = y;
	return (1);
}

/**
 * _putfd - writes the character c to given filed
 * @y: The character to print
 * @filed: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char y, int filed)
{
	static int v;
	static char buf[WRITE_BUF_SIZE];

	if (y == BUF_FLUSH || v >= WRITE_BUF_SIZE)
	{
		write(filed, buf, v);
		v = 0;
	}
	if (y != BUF_FLUSH)
		buf[v++] = y;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @sttring: the string to be printed
 * @filed: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *sttring, int filed)
{
	int v = 0;

	if (!sttring)
		return (0);
	while (*sttring)
	{
		v += _putfd(*sttring++, filed);
	}
	return (v);
}
