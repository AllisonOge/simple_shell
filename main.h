#ifndef MAIN_H
#define MAIN_H

#define BUFF_SIZE 1024
#include <stdio.h>

/**********MAIN FUNCTIONS***************/
char **parsecmd(char *, char **);
void runcmd(char **, int *, char *, char **);

/**********BUILTINS FUNCTIONS*************/
void printenv(char **);
void _cd(char *, char *);
char *getcmdpath(char *, char **);

/**********CUSTOM FUNCTIONS**************/
char *_strtok(char *, const char *);
ssize_t _getline(char **, size_t *, int);

/**********HELPER FUNCTIONS**************/
ssize_t _read(int, char *, size_t);

#endif /* MAIN_H */
