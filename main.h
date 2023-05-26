#ifndef MAIN_H
#define MAIN_H

#define BUFF_SIZE 1024
#include <stdio.h>
#include <stdlib.h>

/**********MAIN FUNCTIONS***************/
char **parsecmd(char *, char **);
void runcmd(char **, int *, char *, char **);
ssize_t getcmd(char **, size_t *, char *);

/**********BUILTINS FUNCTIONS*************/
void printenv(char **);
int _cd(char *, char *);
void exitshell(char *, int *);
int isbuiltin(char **, char **, char *, int *);

/**********HELPER FUNCTIONS***************/
char *getcmdpath(char *, char **);

/**********FUNCTION WRAPPERS**************/
pid_t my_fork(void);

#endif /* MAIN_H */
