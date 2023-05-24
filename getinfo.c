#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @adstr: struct address
 */
void clear_info(info_t *adstr)
{
	adstr->arg = NULL;
	adstr->argv = NULL;
	adstr->path = NULL;
	adstr->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @adstr: struct address
 * @arv: argument vector
 */
void set_info(info_t *adstr, char **arv)
{
	int x = 0;

	adstr->fname = arv[0];
	if (adstr->arg)
	{
		adstr->argv = strtow(adstr->arg, " \t");
		if (!adstr->argv)
		{

			adstr->argv = malloc(sizeof(char *) * 2);
			if (adstr->argv)
			{
				adstr->argv[0] = _strdup(adstr->arg);
				adstr->argv[1] = NULL;
			}
		}
		for (x = 0; adstr->argv && adstr->argv[x]; x++)
			;
		adstr->argc = x;

		replace_alias(adstr);
		replace_vars(adstr);
	}
}

/**
 * free_info - frees info_t struct fields
 * @adstr: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *adstr, int all)
{
	ffree(adstr->argv);
	adstr->argv = NULL;
	adstr->path = NULL;
	if (all)
	{
		if (!adstr->cmd_buf)
			free(adstr->arg);
		if (adstr->env)
			free_list(&(adstr->env));
		if (adstr->history)
			free_list(&(adstr->history));
		if (adstr->alias)
			free_list(&(adstr->alias));
		ffree(adstr->environ);
			adstr->environ = NULL;
		bfree((void **)adstr->cmd_buf);
		if (adstr->readfd > 2)
			close(adstr->readfd);
		_putchar(BUF_FLUSH);
	}
}
