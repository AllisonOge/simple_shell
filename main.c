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
* Return: exit code of the program
*/
int main(int ac __attribute__((unused)), char **av, char **env)
{
	int status;
	char *cmdline = NULL;
	size_t len = 0;
	char *argv[100];

	while (getcmd(&cmdline, &len, "($) ") != -1)
	{
		if (cmdline[0] == '\n')
			continue;
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
	}
	free(cmdline);

	if (feof(stdin) && isatty(STDIN_FILENO))
	{
		write(1, "\n", 1);
	}
	return (WEXITSTATUS(status));
}
