#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
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
*/
void runcmd(char **argv, int *status)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        if (execve(argv[0], argv, NULL) == -1)
        {
            perror("Error");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("Error");
    }
    else
    {
        do
        {
            waitpid(pid, status, WUNTRACED);
        } while (!WIFEXITED(*status) && !WIFSIGNALED(*status));
        /* printf("exit code -> %d\n", WEXITSTATUS(*status)); */
    }
}