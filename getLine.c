#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @strprm: parameter struct
 * @adbuf: address of buffer
 * @adlen: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *strprm, char **adbuf, size_t *adlen)
{
	ssize_t k = 0;
	size_t prlen = 0;

	if (!*adlen) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*adbuf);
		*adbuf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(adbuf, &prlen, stdin);
#else
		k = _getline(strprm, adbuf, &prlen);
#endif
		if (k > 0)
		{
			if ((*adbuf)[k - 1] == '\n')
			{
				(*adbuf)[k - 1] = '\0'; /* remove trailing newline */
				k--;
			}
			strprm->linecount_flag = 1;
			remove_comments(*adbuf);
			build_history_list(strprm, *adbuf, strprm->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*adlen = k;
				strprm->cmd_buf = adbuf;
			}
		}
	}
	return (k);
}

/**
 * get_input - gets a line minus the newline
 * @strprm: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *strprm)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t x, y, len;
	ssize_t k = 0;
	char **buf_p = &(strprm->arg), *p;

	_putchar(BUF_FLUSH);
	k = input_buf(strprm, &buf, &len);
	if (k == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		y = x; /* init new iterator to current buf position */
		p = buf + x; /* get pointer for return */

		check_chain(strprm, buf, &y, x, len);
		while (y < len) /* iterate to semicolon or end */
		{
			if (is_chain(strprm, buf, &y))
				break;
			y++;
		}

		x = y + 1; /* increment past nulled ';'' */
		if (x >= len) /* reached end of buffer? */
		{
			x = len = 0; /* reset position and length */
			strprm->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (k); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @strprm: parameter struct
 * @buf: buffer
 * @sz: size
 *
 * Return: k
 */
ssize_t read_buf(info_t *strprm, char *buf, size_t *sz)
{
	ssize_t k = 0;

	if (*sz)
		return (0);
	k = read(strprm->readfd, buf, READ_BUF_SIZE);
	if (k >= 0)
		*sz = k;
	return (k);
}

/**
 * _getline - gets the next line of input from STDIN
 * @strprm: parameter struct
 * @adptr: address of pointer to buffer, preallocated or NULL
 * @szptr: size of preallocated ptr buffer if not NULL
 *
 * Return: w
 */
int _getline(info_t *strprm, char **adptr, size_t *szptr)
{
	static char buf[READ_BUF_SIZE];
	static size_t x, len;
	size_t k;
	ssize_t z = 0, w = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *adptr;
	if (p && szptr)
		w = *szptr;
	if (x == len)
		x = len = 0;

	z = read_buf(strprm, buf, &len);
	if (z == -1 || (z == 0 && len == 0))
		return (-1);

	c = _strchr(buf + x, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, w, w ? w + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (w)
		_strncat(new_p, buf + x, k - x);
	else
		_strncpy(new_p, buf + x, k - x + 1);

	w += k - x;
	x = k;
	p = new_p;

	if (szptr)
		*szptr = w;
	*adptr = p;
	return (w);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sigl_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sigl_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
