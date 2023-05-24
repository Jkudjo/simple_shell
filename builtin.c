#include "shell.h"

/**
 * _myexit - exits the shell
 * @know: a way of Structure contains potential arguments. Used to maintain
 *         the constant function.
 *  Return: exit with a value that given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *know)
{
	int exit_checking;

	if (know->argv[1])  /* If found any exit arguement after checking*/
	{
		exit_checking = _erratoi(know->argv[1]);
		if (exit_checking == -1)
		{
			know->status = 2;
			print_error(know, "Illegal number: ");
			_eputs(know->argv[1]);
			_eputchar('\n');
			return (1);
		}
		know->err_num = _erratoi(know->argv[1]);
		return (-2);
	}
	know->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @know: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd(info_t *know)
{
	char *c, *directory, buffer[1024];
	int change_dir;

	c = getcwd(buffer, 1024);
	if (!c)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!know->argv[1])
	{
		directory = _getenv(know, "HOME=");
		if (!directory)
			change_dir = /* TODO: what should this be? */
				chdir((directory = _getenv(know, "PWD=")) ? directory : "/");
		else
			change_dir = chdir(directory);
	}
	else if (_strcmp(know->argv[1], "-") == 0)
	{
		if (!_getenv(know, "OLDPWD="))
		{
			_puts(c);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(know, "OLDPWD=")), _putchar('\n');
		change_dir = /* TODO: what should this be? */
			chdir((directory = _getenv(know, "OLDPWD=")) ? directory : "/");
	}
	else
		change_dir = chdir(know->argv[1]);
	if (change_dir == -1)
	{
		print_error(know, "can't cd to ");
		_eputs(know->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(know, "OLDPWD", _getenv(know, "PWD="));
		_setenv(know, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @know: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(info_t *know)
{
	char **arrg_array;

	arrg_array = know->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arrg_array); /* temp att_unused workaround */
	return (0);
}
