#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
* main - entry point
* @ac: the number of arguments
* @av: the array of arguments
* @env: the array of environment variables
*
* Return: Always 0 (Success)
*/
int main(int ac __attribute__((unused)), char **av, char **env)
{
	int tty = 0, status = 0;
	char *cmdline = NULL;
	size_t len = 0;
	char *argv[100];

	if (isatty(STDIN_FILENO))
	{
		tty = 1;
		write(1, "$ ", 2);
	}
	while (getline(&cmdline, &len, stdin) != -1)
	{
		if (cmdline[0] == '\n')
		{
			if (tty)
				write(1, "$ ", 2);
			continue;
		}
		if (strncmp(cmdline, "exit", 4) == 0)
		{
			free(cmdline);
			exit(0);
		} else if (strncmp(cmdline, "env", 3) == 0)
		{
			printenv(env);
		} else if (strncmp(cmdline, "cd", 2) == 0)
		{
			_cd(cmdline + 3, av[0]);
		} else
		{
			runcmd(parsecmd(cmdline, argv), &status, av[0], env);
		}
		if (tty)
			write(1, "$ ", 2);
	}
	free(cmdline);

	if (feof(stdin))
	{
		write(1, "\n", 1);
	}
	return (WEXITSTATUS(status));
}
