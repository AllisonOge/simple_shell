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
	int status = 0;
	char *cmdline = NULL;
	size_t len = 0;
	ssize_t nread;
	char *argv[100];

	if (isatty(STDIN_FILENO))
	{
		write(1, "$ ", 2);
	}
	while ((nread = _getline(&cmdline, &len, STDIN_FILENO)) > 0)
	{
		if (cmdline[0] == '\n')
		{
			if (isatty(STDIN_FILENO))
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
		} else
		{
			runcmd(parsecmd(cmdline, argv), &status, av[0], env);
		}
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
	}
	free(cmdline);

	if (nread == -2 && isatty(STDIN_FILENO))
	{
		write(1, "\n", 1);
	}
	return (WEXITSTATUS(status));
}
