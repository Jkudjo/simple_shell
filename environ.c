#include "shell.h"

/**
 * _myenv - prints the current environment
 * @know: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *know)
{
	print_list_str(know->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @know: Structure containing potential arguments. Used to maintain
 * @env_name: enviorment var name
 *
 * Return: the value
 */
char *_getenv(info_t *know, const char *env_name)
{
	list_t *alais_node = know->env;
	char *x;

	while (alais_node)
	{
		x = starts_with(alais_node->str, env_name);
		if (x && *x)
			return (x);
		alais_node = alais_node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @know: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *know)
{
	if (know->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(know, know->argv[1], know->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @know: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *know)
{
	int v;

	if (know->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (v = 1; v <= know->argc; v++)
		_unsetenv(know, know->argv[v]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @know: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *know)
{
	list_t *alais_node = NULL;
	size_t v;

	for (v = 0; environ[v]; v++)
		add_node_end(&alais_node, environ[v], 0);
	know->env = alais_node;
	return (0);
}
