#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @strinfo: the info struct
 * @fpath: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *strinfo, char *fpath)
{
	struct stat st;

	(void)strinfo;
	if (!fpath || stat(fpath, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @strtindx: starting index
 * @stopindx: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int strtindx, int stopindx)
{
	static char buf[1024];
	int x = 0, z = 0;

	for (z = 0, x = strtindx; x < stopindx; x++)
		if (pathstr[x] != ':')
			buf[z++] = pathstr[x];
	buf[z] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @strinfo: the info struct
 * @pathstr: the PATH string
 * @fcmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *strinfo, char *pathstr, char *fcmd)
{
	int x = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(fcmd) > 2) && starts_with(fcmd, "./"))
	{
		if (is_cmd(strinfo, fcmd))
			return (fcmd);
	}
	while (1)
	{
		if (!pathstr[x] || pathstr[x] == ':')
		{
			path = dup_chars(pathstr, curr_pos, x);
			if (!*path)
				_strcat(path, fcmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, fcmd);
			}
			if (is_cmd(strinfo, path))
				return (path);
			if (!pathstr[x])
				break;
			curr_pos = x;
		}
		x++;
	}
	return (NULL);
}
