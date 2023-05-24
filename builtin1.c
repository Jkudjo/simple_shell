#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @know: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *know)
{
	print_list(know->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @know: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error ocuured
 */
int unset_alias(info_t *know, char *str)
{
	char *x, y;
	int var;

	x = _strchr(str, '=');
	if (!x)
		return (1);
	y = *x;
	*x = 0;
	var = delete_node_at_index(&(know->alias),
		get_node_index(know->alias, node_starts_with(know->alias, str, -1)));
	*x = y;
	return (var);
}

/**
 * set_alias - sets alias to string
 * @know: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *know, char *str)
{
	char *x;

	x = _strchr(str, '=');
	if (!x)
		return (1);
	if (!*++x)
		return (unset_alias(know, str));

	unset_alias(know, str);
	return (add_node_end(&(know->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @al_node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *al_node)
{
	char *x = NULL, *aa = NULL;

	if (al_node)
	{
		x = _strchr(al_node->str, '=');
		for (aa = al_node->str; aa <= x; aa++)
			_putchar(*aa);
		_putchar('\'');
		_puts(x + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @know: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *know)
{
	int v = 0;
	char *x = NULL;
	list_t *al_node = NULL;

	if (know->argc == 1)
	{
		al_node = know->alias;
		while (al_node)
		{
			print_alias(al_node);
			al_node = al_node->next;
		}
		return (0);
	}
	for (v = 1; know->argv[v]; v++)
	{
		x = _strchr(know->argv[v], '=');
		if (x)
			set_alias(know, know->argv[v]);
		else
			print_alias(node_starts_with(know->alias, know->argv[v], '='));
	}

	return (0);
}
