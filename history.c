#include "shell.h"

/**
 * get_history_file - gets the history file
 * @prmstr: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *prmstr)
{
	char *buf, *dir;

	dir = _getenv(prmstr, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @prmstr: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *prmstr)
{
	ssize_t fc;
	char *filename = get_history_file(prmstr);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fc = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fc == -1)
		return (-1);
	for (node = prmstr->history; node; node = node->next)
	{
		_putsfd(node->str, fc);
		_putfd('\n', fc);
	}
	_putfd(BUF_FLUSH, fc);
	close(fc);
	return (1);
}

/**
 * read_history - reads history from file
 * @prmstr: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *prmstr)
{
	int x, last = 0, linecount = 0;
	ssize_t fc, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(prmstr);

	if (!filename)
		return (0);

	fc = open(filename, O_RDONLY);
	free(filename);
	if (fc == -1)
		return (0);
	if (!fstat(fc, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fc, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fc);
	for (x = 0; x < fsize; x++)
		if (buf[x] == '\n')
		{
			buf[x] = 0;
			build_history_list(prmstr, buf + last, linecount++);
			last = x + 1;
		}
	if (last != x)
		build_history_list(prmstr, buf + last, linecount++);
	free(buf);
	prmstr->histcount = linecount;
	while (prmstr->histcount-- >= HIST_MAX)
		delete_node_at_index(&(prmstr->history), 0);
	renumber_history(prmstr);
	return (prmstr->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @arstrct: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @hisln: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *arstrct, char *buf, int hisln)
{
	list_t *node = NULL;

	if (arstrct->history)
		node = arstrct->history;
	add_node_end(&node, buf, hisln);

	if (!arstrct->history)
		arstrct->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @arstrct: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *arstrct)
{
	list_t *node = arstrct->history;
	int x = 0;

	while (node)
	{
		node->num = x++;
		node = node->next;
	}
	return (arstrct->histcount = x);
}
