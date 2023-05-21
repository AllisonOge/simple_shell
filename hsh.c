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
	char *delimiters = " \n\t";

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
	int errnum;
	struct stat st;

	/* check if command exit */
	if (stat(argv[0], &st) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(argv[0], argv, env) == -1)
			{
				errnum = errno;
				perror("Error");
				exit(errnum);
			}
		}
		else if (pid < 0)
		{
			perror("Error");
		}
		else
		{
			do {
				waitpid(pid, status, WUNTRACED);
			} while (!WIFEXITED(*status) && !WIFSIGNALED(*status));
			/*
			* printf("error number -> %d\n", errno);
			* printf("exit code -> %d\n", WEXITSTATUS(*status));
			* printf("exit signal -> %d\n", WTERMSIG(*status));
			*/
		}
	} else
	{
		*status = 32512;
		dprintf(STDERR_FILENO, "%s: 1: %s: not found\n", pgm, argv[0]);
	}
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
 * _cd - change the current working directory
 * @filepath: the path to the directory
 * @pgm: the name of the program
*/
void _cd(char *filepath, char *pgm)
{
	int errnum;
	struct stat st;

	if (stat(filepath, &st) == 0)
	{
		if (chdir(filepath) == -1)
		{
			errnum = errno;
			perror("Error");
			exit(errnum);
		}
	} else
	{
		dprintf(STDERR_FILENO, "%s: 1: cd: can't cd to %s\n", pgm, filepath);
	}
}
