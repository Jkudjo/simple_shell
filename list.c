#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @phn: address of pointer to head node
 * @fstrn: str field of node
 * @nih: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **phn, const char *fstrn, int nih)
{
	list_t *new_head;

	if (!phn)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = nih;
	if (fstrn)
	{
		new_head->str = _strdup(fstrn);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *phn;
	*phn = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @phn: address of pointer to head node
 * @fstrn: str field of node
 * @nih: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **phn, const char *fstrn, int nih)
{
	list_t *new_node, *node;

	if (!phn)
		return (NULL);

	node = *phn;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = nih;
	if (fstrn)
	{
		new_node->str = _strdup(fstrn);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*phn = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @pfn: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *pfn)
{
	size_t x = 0;

	while (pfn)
	{
		_puts(pfn->str ? pfn->str : "(nil)");
		_puts("\n");
		pfn = pfn->next;
		x++;
	}
	return (x);
}

/**
 * delete_node_at_index - deletes node at given index
 * @adpfn: address of pointer to first node
 * @indx: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **adpfn, unsigned int indx)
{
	list_t *node, *prev_node;
	unsigned int x = 0;

	if (!adpfn || !*adpfn)
		return (0);

	if (!indx)
	{
		node = *adpfn;
		*adpfn = (*adpfn)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *adpfn;
	while (node)
	{
		if (x == indx)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		x++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @adphn: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **adphn)
{
	list_t *node, *next_node, *head;

	if (!adphn || !*adphn)
		return;
	head = *adphn;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*adphn = NULL;
}
