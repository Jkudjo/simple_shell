#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode always
 * @know: struct address
 *
 * Return: 1 if interactive mode, 0 if not
 */
int interactive(info_t *know)
{
	return (isatty(STDIN_FILENO) && know->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @x: the char to check
 * @delimeter: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char x, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == x)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@x: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int x)
{
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts datatype from string to an integer
 *@a: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *a)
{
	int v, score = 1, ensign = 0, oput;
	unsigned int effect = 0;

	for (v = 0;  a[v] != '\0' && ensign != 2; v++)
	{
		if (a[v] == '-')
			score *= -1;

		if (a[v] >= '0' && a[v] <= '9')
		{
			ensign = 1;
			effect *= 10;
			effect += (a[v] - '0');
		}
		else if (ensign == 1)
			ensign = 2;
	}

	if (score == -1)
		oput = -effect;
	else
		oput = effect;

	return (oput);
}
