#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @prmstr: the parameter struct
 * @buf: the char buffer
 * @adp: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *prmstr, char *buf, size_t *adp)
{
	size_t y = *adp;

	if (buf[y] == '|' && buf[y + 1] == '|')
	{
		buf[y] = 0;
		y++;
		prmstr->cmd_buf_type = CMD_OR;
	}
	else if (buf[y] == '&' && buf[y + 1] == '&')
	{
		buf[y] = 0;
		y++;
		prmstr->cmd_buf_type = CMD_AND;
	}
	else if (buf[y] == ';') /* found end of this command */
	{
		buf[y] = 0; /* replace semicolon with null */
		prmstr->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*adp = y;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @prmstr: the parameter struct
 * @buf: the char buffer
 * @adp: address of current position in buf
 * @sp: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *prmstr, char *buf, size_t *adp, size_t sp, size_t len)
{
	size_t y = *adp;

	if (prmstr->cmd_buf_type == CMD_AND)
	{
		if (prmstr->status)
		{
			buf[sp] = 0;
			y = len;
		}
	}
	if (prmstr->cmd_buf_type == CMD_OR)
	{
		if (!prmstr->status)
		{
			buf[sp] = 0;
			y = len;
		}
	}

	*adp = y;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @prmstr: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *prmstr)
{
	int x;
	list_t *node;
	char *p;

	for (x = 0; x < 10; x++)
	{
		node = node_starts_with(prmstr->alias, prmstr->argv[0], '=');
		if (!node)
			return (0);
		free(prmstr->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		prmstr->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @prmstr: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *prmstr)
{
	int x = 0;
	list_t *node;

	for (x = 0; prmstr->argv[x]; x++)
	{
		if (prmstr->argv[x][0] != '$' || !prmstr->argv[x][1])
			continue;

		if (!_strcmp(prmstr->argv[x], "$?"))
		{
			replace_string(&(prmstr->argv[x]),
				_strdup(convert_number(prmstr->status, 10, 0)));
			continue;
		}
		if (!_strcmp(prmstr->argv[x], "$$"))
		{
			replace_string(&(prmstr->argv[x]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(prmstr->env, &prmstr->argv[x][1], '=');
		if (node)
		{
			replace_string(&(prmstr->argv[x]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&prmstr->argv[x], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @oldstr: address of old string
 * @newstr: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **oldstr, char *newstr)
{
	free(*oldstr);
	*oldstr = newstr;
	return (1);
}
