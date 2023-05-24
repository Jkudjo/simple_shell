#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @inst: the input string
 * @dst: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *inst, char *dst)
{
	int x, y, z, r, numwords = 0;
	char **w;

	if (inst == NULL || inst[0] == 0)
		return (NULL);
	if (!dst)
		dst = " ";
	for (x = 0; inst[x] != '\0'; x++)
		if (!is_delim(inst[x], dst) && (is_delim(inst[x + 1], dst) || !inst[x + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	w = malloc((1 + numwords) * sizeof(char *));
	if (!w)
		return (NULL);
	for (x = 0, y = 0; y < numwords; y++)
	{
		while (is_delim(inst[x], dst))
			x++;
		z = 0;
		while (!is_delim(inst[x + z], dst) && inst[x + z])
			z++;
		w[y] = malloc((z + 1) * sizeof(char));
		if (!w[y])
		{
			for (z = 0; z < y; z++)
				free(w[z]);
			free(w);
			return (NULL);
		}
		for (r = 0; r < z; r++)
			w[y][r] = inst[x++];
		w[y][r] = 0;
	}
	w[y] = NULL;
	return (w);
}

/**
 * **strtow2 - splits a string into words
 * @inst: the input string
 * @dst: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *inst, char dst)
{
	int x, y, z, r, numwords = 0;
	char **w;

	if (inst == NULL || inst[0] == 0)
		return (NULL);
	for (x = 0; inst[x] != '\0'; x++)
		if ((inst[x] != dst && inst[x + 1] == dst) ||
		    (inst[x] != dst && !inst[x + 1]) || inst[x + 1] == dst)
			numwords++;
	if (numwords == 0)
		return (NULL);
	w = malloc((1 + numwords) * sizeof(char *));
	if (!w)
		return (NULL);
	for (x = 0, y = 0; y < numwords; y++)
	{
		while (inst[x] == dst && inst[x] != dst)
			x++;
		z = 0;
		while (inst[x + z] != dst && inst[x + z] && inst[x + z] != dst)
			z++;
		w[y] = malloc((z + 1) * sizeof(char));
		if (!w[y])
		{
			for (z = 0; z < y; z++)
				free(w[z]);
			free(w);
			return (NULL);
		}
		for (r = 0; r < z; r++)
			w[y][r] = inst[x++];
		w[y][r] = 0;
	}
	w[y] = NULL;
	return (w);
}
