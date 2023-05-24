#include "shell.h"

/**
 * list_len - determines length of linked list
 * @pfn: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *pfn)
{
	size_t x = 0;

	while (pfn)
	{
		pfn = pfn->next;
		x++;
	}
	return (x);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @pfn: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *pfn)
{
	list_t *node = pfn;
	size_t x = list_len(pfn), y;
	char **strs;
	char *str;

	if (!pfn || !x)
		return (NULL);
	strs = malloc(sizeof(char *) * (x + 1));
	if (!strs)
		return (NULL);
	for (x = 0; node; node = node->next, x++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (y = 0; y < x; y++)
				free(strs[y]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[x] = str;
	}
	strs[x] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @pfn: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *pfn)
{
	size_t x = 0;

	while (pfn)
	{
		_puts(convert_number(pfn->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(pfn->str ? pfn->str : "(nil)");
		_puts("\n");
		pfn = pfn->next;
		x++;
	}
	return (x);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @plh: pointer to list head
 * @strmat: string to match
 * @ch: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *plh, char *strmat, char ch)
{
	char *p = NULL;

	while (plh)
	{
		p = starts_with(plh->str, strmat);
		if (p && ((ch == -1) || (*p == ch)))
			return (plh);
		plh = plh->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @plh: pointer to list head
 * @ptn: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *plh, list_t *ptn)
{
	size_t x = 0;

	while (plh)
	{
		if (plh == ptn)
			return (x);
		plh = plh->next;
		x++;
	}
	return (-1);
}
