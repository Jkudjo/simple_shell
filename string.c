#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @strg: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *strg)
{
	int x = 0;

	if (!strg)
		return (0);

	while (*strg++)
		x++;
	return (x);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @st1: the first strang
 * @st2: the second strang
 *
 * Return: negative if st1 < st2, positive if st1 > st2, zero if st1 == st2
 */
int _strcmp(char *st1, char *st2)
{
	while (*st1 && *st2)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
	}
	if (*st1 == *st2)
		return (0);
	else
		return (*st1 < *st2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @strsr: string to search
 * @sbstr: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *strsr, const char *sbstr)
{
	while (*sbstr)
		if (*sbstr++ != *strsr++)
			return (NULL);
	return ((char *)strsr);
}

/**
 * _strcat - concatenates two strings
 * @dst: the destination buffer
 * @bfsrc: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dst, char *bfsrc)
{
	char *ret = dst;

	while (*dst)
		dst++;
	while (*bfsrc)
		*dst++ = *bfsrc++;
	*dst = *bfsrc;
	return (ret);
}
