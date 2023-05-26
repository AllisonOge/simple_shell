#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * getcmd - prompt in tty mode and read the command line
 * @cmdline: the command line string
 * @len: the length of the command line
 * @prompt: the prompt to display
 *
 * Return: the length of the command line or -1 if failed
*/
ssize_t getcmd(char **cmdline, size_t *len, char *prompt)
{
	if (isatty(STDIN_FILENO))
	{
		write(1, prompt, strlen(prompt));
	}
	return (getline(cmdline, len, stdin));
}

/**
 * parsecmd - parse the command line and tokenize the string
 * @cmdline: the command line string
 * @argv: the array of strings to store the tokens
 *
 * Return: the array of strings containing the tokens
*/
char **parsecmd(char *cmdline, char **argv)
{
	char *token;
	int i = 0;
	char *delimiters = " \n\t\v\r";

	token = strtok(cmdline, delimiters);
	while (token != NULL)
	{
		argv[i] = token;
		token = strtok(NULL, delimiters);
		i++;
	}
	argv[i] = NULL;

	return (argv);
}


/**
 * runcmd - fork and execute the command
 * @argv: the array of strings containing the command and its arguments
 * @status: the exit status
 * @pgm: the name of the program
 * @env: the array of environment variables
*/
void runcmd(char **argv, int *status, char *pgm, char **env)
{
	pid_t pid;
	char *cmdpath = NULL, buf[BUFF_SIZE];
	struct stat st;

	if (argv[0] == NULL)
		return;
	/* check if command is built-in */
	if (isbuiltin(argv, env, pgm, status) == 1)
		return;
	/* check if command exit */
	if (stat(argv[0], &st) != 0)
	{
		/* get the fullpath from the env */
		cmdpath = getcmdpath(argv[0], env);
		if (!cmdpath)
		{
			*status = 32512;
			dprintf(STDERR_FILENO, "%s: 1: %s: not found\n", pgm, argv[0]);
			return;
		}
		strcpy(buf, cmdpath);
		argv[0] = buf;
		free(cmdpath);
	}

	/* fork and execute command */
	pid = my_fork();
	if (pid == 0)
	{
		if (execve(argv[0], argv, env) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	} else if (pid > 0)
	{
		do {
			waitpid(pid, status, WUNTRACED);
		} while (!WIFEXITED(*status) && !WIFSIGNALED(*status));
	}
}
