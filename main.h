#ifndef MAIN_H
#define MAIN_H

/*
 *The kjxjhcjxh
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

/*
 *thebse aibfbskf
 */
void show_prompt(void);
void PRINT(const char *message);
void parse_command(char *command, size_t size);
void execute_command(const char *command);




#endif /* SHELL_H */
