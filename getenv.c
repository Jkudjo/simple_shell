#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @arstrct: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *arstrct)
{
	if (!arstrct->environ || arstrct->env_changed)
	{
		arstrct->environ = list_to_strings(arstrct->env);
		arstrct->env_changed = 0;
	}

	return (arstrct->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @arstrct: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @strvar: the string env var property
 */
int _unsetenv(info_t *arstrct, char *strvar)
{
	list_t *node = arstrct->env;
	size_t x = 0;
	char *p;

	if (!node || !strvar)
		return (0);

	while (node)
	{
		p = starts_with(node->str, strvar);
		if (p && *p == '=')
		{
			arstrct->env_changed = delete_node_at_index(&(arstrct->env), x);
			x = 0;
			node = arstrct->env;
			continue;
		}
		node = node->next;
		x++;
	}
	return (arstrct->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @arstrct: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @strvar: the string env var property
 * @strval: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *arstrct, char *strvar, char *strval)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!strvar || !strval)
		return (0);

	buf = malloc(_strlen(strvar) + _strlen(strval) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, strvar);
	_strcat(buf, "=");
	_strcat(buf, strval);
	node = arstrct->env;
	while (node)
	{
		p = starts_with(node->str, strvar);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			arstrct->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(arstrct->env), buf, 0);
	free(buf);
	arstrct->env_changed = 1;
	return (0);
}
