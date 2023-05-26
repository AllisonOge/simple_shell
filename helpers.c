#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

/**********HELPER FUNCTIONS***************/
/**
 * getcmdpath - get the full path of the command
 * @cmd: the command
 * @env: the array of environment variables
 *
 * Return: the full path of the command
*/
char *getcmdpath(char *cmd, char **env)
{
	char *path = NULL, fullpath[BUFF_SIZE];
	char *token;
	char *delimiters = ": \n\t\v\r";
	int i = 0;
	struct stat st;

	while (env[i] != NULL)
	{
		if (strncmp(env[i], "PATH", 4) == 0)
		{
			path = strdup(env[i] + 5);
			break;
		}
		i++;
	}
	token = strtok(path, delimiters);
	while (token != NULL)
	{
		strcat(strcpy(fullpath, token), "/");
		strcat(strcat(fullpath, cmd), "\0");
		if (stat(fullpath, &st) == 0)
		{
			free(path);
			return (strdup(fullpath));
		}
		token = strtok(NULL, delimiters);
	}
	free(path);
	return (NULL);
}

/**
 * my_fork - wrapper for fork
 *
 * Return: the pid of the child process
 */
pid_t my_fork(void)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
	}
	return (pid);
}
