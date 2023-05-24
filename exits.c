#include "shell.h"

/**
 **_strncpy - copies a string
 *@dst: the destination string to be copied to
 *@strsrc: the source string
 *@nc: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dst, char *strsrc, int nc)
{
	int x, y;
	char *w = dst;

	x = 0;
	while (strsrc[x] != '\0' && x < nc - 1)
	{
		dst[x] = strsrc[x];
		x++;
	}
	if (x < nc)
	{
		y = x;
		while (y < nc)
		{
			dst[y] = '\0';
			y++;
		}
	}
	return (w);
}

/**
 **_strncat - concatenates two strings
 *@frststr: the first string
 *@sndstr: the second string
 *@nb: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *frststr, char *sndstr, int nb)
{
	int x, y;
	char *w = frststr;

	x = 0;
	y = 0;
	while (frststr[x] != '\0')
		x++;
	while (sndstr[y] != '\0' && y < nb)
	{
		frststr[x] = sndstr[y];
		x++;
		y++;
	}
	if (y < nb)
		frststr[x] = '\0';
	return (w);
}

/**
 **_strchr - locates a character in a string
 *@st: the string to be parsed
 *@ch: the character to look for
 *Return: (st) a pointer to the memory area st
 */
char *_strchr(char *st, char ch)
{
	do {
		if (*st == ch)
			return (st);
	} while (*st++ != '\0');

	return (NULL);
}
