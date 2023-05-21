#ifndef MAIN_H
#define MAIN_H

#define BUFF_SIZE 1024

/**********MAIN FUNCTIONS***************/
char **parsecmd(char *, char **);
void runcmd(char **, int *, char *, char **);

/**********BUILTINS FUNCTIONS*************/
void printenv(char **);
void _cd(char *, char *);
char *getcmdpath(char *, char **);

#endif /* MAIN_H */
