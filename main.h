#ifndef MAIN_H
#define MAIN_H

/*---LIBRARIES---*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/*---MACROS---*/
#define TOK_DELIM " \t\r\n\a\""
extern char **environ;

/*---PROTOTYPES---*/
void interactive_mode(void);
void no_interactive_mode(void);

/*---INTERACTIVE_MODE---*/
char *read_line(void);
char **tokenizer(char *line);
int executor(char **args);

/*---EXECUTOR---*/
int new_process(char **args);

/*---NO_INTERACTIVE_MODE---*/
char *read_stream(void);

/*<---BUILTIN FUNC--->*/
int my_cd(char **args);
int my_exit(char **args);
int my_env(char **args);

#endif

