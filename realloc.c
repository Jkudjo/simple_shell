#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@m: the pointer to the memory area
 *@b: the byte to fill *m with
 *@nb: the amount of bytes to be filled
 *Return: (m) a pointer to the memory area m
 */
char *_memset(char *m, char b, unsigned int nb)
{
	unsigned int x;

	for (x = 0; x < nb; x++)
		m[x] = b;
	return (m);
}

/**
 * ffree - frees a string of strings
 * @ss: string of strings
 */
void ffree(char **ss)
{
	char **a = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @old_ptr: pointer to previous malloc'ated block
 * @old_bsize: byte size of previous block
 * @new_bsize: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *old_ptr, unsigned int old_bsize, unsigned int new_bsize)
{
	char *p;

	if (!old_ptr)
		return (malloc(new_bsize));
	if (!new_bsize)
		return (free(old_ptr), NULL);
	if (new_bsize == old_bsize)
		return (old_ptr);

	p = malloc(new_bsize);
	if (!p)
		return (NULL);

	old_bsize = old_bsize < new_bsize ? old_bsize : new_bsize;
	while (old_bsize--)
		p[old_bsize] = ((char *)old_ptr)[old_bsize];
	free(old_ptr);
	return (p);
}
