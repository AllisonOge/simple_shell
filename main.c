#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
* main - entry point
*
* Return: Always 0 (Success)
*/
int main(void)
{
	int tty = 0;
	char *cmdline = NULL;
	int status = 0;
	size_t len = 0;
	char* argv[100];

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
		}
		runcmd(parsecmd(cmdline, argv), &status);
		if (tty)
			write(1, "$ ", 2);
	}

	if (feof(stdin))
	{
		write(1, "\n", 1);
	}
	return (WEXITSTATUS(status));
}
