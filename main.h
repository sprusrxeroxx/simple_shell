#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//for use with the strtok function, delimiters are space characters
#define TOK_BUFSIZE 64
#define DELIMITERS " \t\n\r\a\v\f"
#define MAX_VAR_NAME_LEN 256
#define MAX_VAR_VALUE_LEN 256

//used to print out the environment variables
extern char **environ;

//declaration of read, parse, execute, and launch functions
char *read_line(void);
char **parse_line(char *line);
int execute(char **args);
int launch_no_wait(char **args);
int redirection(char **args);
int pipes(char **args);

//declaration of internal functions
int cd(char **args);
int clr(char **args);
int dir(char **args);
int env(char **args);
int echo(char **args);
int help(char **args);
int _pause(char **args);
int quit(char **args);
int set_env_var(char **args);

#endif
