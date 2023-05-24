#include "shell.h"

/**
 * hsh - main shell loop
 * @prminfo: the parameter & return info struct
 * @arv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *prminfo, char **arv)
{
	ssize_t k = 0;
	int builtin_ret = 0;

	while (k != -1 && builtin_ret != -2)
	{
		clear_info(prminfo);
		if (interactive(prminfo))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		k = get_input(prminfo);
		if (k != -1)
		{
			set_info(prminfo, arv);
			builtin_ret = find_builtin(prminfo);
			if (builtin_ret == -1)
				find_cmd(prminfo);
		}
		else if (interactive(prminfo))
			_putchar('\n');
		free_info(prminfo, 0);
	}
	write_history(prminfo);
	free_info(prminfo, 1);
	if (!interactive(prminfo) && prminfo->status)
		exit(prminfo->status);
	if (builtin_ret == -2)
	{
		if (prminfo->err_num == -1)
			exit(prminfo->status);
		exit(prminfo->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @prminfo: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *prminfo)
{
	int x, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (_strcmp(prminfo->argv[0], builtintbl[x].type) == 0)
		{
			prminfo->line_count++;
			built_in_ret = builtintbl[x].func(prminfo);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @prminfo: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *prminfo)
{
	char *path = NULL;
	int x, r;

	prminfo->path = prminfo->argv[0];
	if (prminfo->linecount_flag == 1)
	{
		prminfo->line_count++;
		prminfo->linecount_flag = 0;
	}
	for (x = 0, r = 0; prminfo->arg[x]; x++)
		if (!is_delim(prminfo->arg[x], " \t\n"))
			r++;
	if (!r)
		return;

	path = find_path(prminfo, _getenv(prminfo, "PATH="), prminfo->argv[0]);
	if (path)
	{
		prminfo->path = path;
		fork_cmd(prminfo);
	}
	else
	{
		if ((interactive(prminfo) || _getenv(prminfo, "PATH=")
			|| prminfo->argv[0][0] == '/') && is_cmd(prminfo, prminfo->argv[0]))
			fork_cmd(prminfo);
		else if (*(prminfo->arg) != '\n')
		{
			prminfo->status = 127;
			print_error(prminfo, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @prminfo: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *prminfo)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(prminfo->path, prminfo->argv, get_environ(prminfo)) == -1)
		{
			free_info(prminfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(prminfo->status));
		if (WIFEXITED(prminfo->status))
		{
			prminfo->status = WEXITSTATUS(prminfo->status);
			if (prminfo->status == 126)
				print_error(prminfo, "Permission denied\n");
		}
	}
}
