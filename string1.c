#include "shell.h"

/**
 * _strcpy - copies a string
 * @goal: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *goal, char *source)
{
	int v = 0;

	if (goal == source || source == 0)
		return (goal);
	while (source[v])
	{
		goal[v] = source[v];
		v++;
	}
	goal[v] = 0;
	return (goal);
}

/**
 * _strdup - duplicate a string
 * @str_dup: the string to duplicate that
 *
 * Return: pointer to the duplicated string using malloc
 */
char *_strdup(const char *str_dup)
{
	int len = 0;
	char *ptr;

	if (str_dup == NULL)
		return (NULL);
	while (*str_dup++)
		len++;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	for (len++; len--;)
		ptr[len] = *--str_dup;
	return (ptr);
}

/**
 *_puts - prints an input string
 *@printt: the string to be printed
 *
 * Return: Nothing to return
 */
void _puts(char *printt)
{
	int v = 0;

	if (!printt)
		return;
	while (printt[v] != '\0')
	{
		_putchar(printt[v]);
		v++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @x: The character to print
 *
 * Return: On success 1 will be.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char x)
{
	static int v;
	static char buf[WRITE_BUF_SIZE];

	if (x == BUF_FLUSH || v >= WRITE_BUF_SIZE)
	{
		write(1, buf, v);
		v = 0;
	}
	if (x != BUF_FLUSH)
		buf[v++] = x;
	return (1);
}
