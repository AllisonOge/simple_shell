#ifndef MAIN_H
#define MAIN_H

/**********MAIN FUNCTIONS***************/
char **parsecmd(char *, char **);
void runcmd(char **, int *, char *, char **);

/**********BUILTINS FUNCTIONS*************/
void printenv(char **);
void _cd(char *, char *);

#endif /* MAIN_H */
