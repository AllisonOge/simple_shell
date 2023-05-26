#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

/*************BUILTINS*****************/
/**
 * _cd - change directory
 * @directory: directory to change to
 * @pgname: program name
 *
 * Return: 1 on success, 0 on failure
 */
int _cd(char *directory, char *pgname)
{
	char *oldpwd = NULL, *pwd = NULL, *home = NULL, *tmp = NULL;
	int ret = 0;
	struct stat st;

	oldpwd = getenv("OLDPWD");
	pwd = getenv("PWD");
	home = getenv("HOME");

	if (directory == NULL)
	{
		if (home == NULL)
		{
			dprintf(STDERR_FILENO, "%s: No $HOME variable set\n", pgname);
			return (0);
		}
		tmp = strdup(home);
	}
	else if (strcmp(directory, "-") == 0)
	{
		if (oldpwd == NULL)
		{
			dprintf(STDERR_FILENO, "%s: OLDPWD not set\n", pgname);
			return (0);
		}
		tmp = strdup(oldpwd);
	}
	else
		if (stat(directory, &st) == 0)
			tmp = strdup(directory);
		else
		{
			dprintf(STDERR_FILENO, "%s: can't cd to %s\n", pgname, directory);
			return (0);
		}

	if (chdir(tmp) == -1)
	{
		perror(pgname);
		ret = 0;
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (oldpwd != NULL)
			setenv("OLDPWD", oldpwd, 1);
		if (pwd != NULL)
			setenv("PWD", pwd, 1);
		ret = 1;
	}
	free(tmp);
	return (ret);
}

/**
 * printenv - print the environment variables
 * @env: the array of environment variables
*/
void printenv(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

/**
 * exitshell - exit the shell
 * @exit_code: the exit code
*/
void exitshell(char *exit_code, int *status)
{
	int code = 0;

	if (exit_code == NULL)
		exit(WEXITSTATUS(*status));
	if (isdigit(exit_code[0]) == 0)
	{
		dprintf(STDERR_FILENO, "Error: illegal number %s\n", exit_code);
		*status = 2;
		return;
	}
	code = atoi(exit_code);
	if (code == 0)
		exit(WEXITSTATUS(*status));
	else
		exit(code);
}

/**
 * isbuiltin - check if the command is a builtin
 * @cmd: the command
 * @env: the array of environment variables
 * @pgname: the program name
 * @status: the exit status
 *
 * Return: 1 if builtin, 0 if not
 */
int isbuiltin(char **cmd, char **env, char *pgname, int *status)
{
	if (strcmp(cmd[0], "exit") == 0)
	{
		exitshell(cmd[1], status);
		return (1);
	}
	if (strcmp(cmd[0], "env") == 0)
	{
		printenv(env);
		return (1);
	}
	if (strcmp(cmd[0], "cd") == 0)
	{
		if (_cd(cmd[1], pgname) == 0)
			*status = 2;
		return (1);
	}
	return (0);
}
