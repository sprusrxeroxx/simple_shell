#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


char *strtok(char *str, const char *delim);
void execmd(char **argv);
char *get_location(char *command);
int stat(const char *pathname, struct stat *statbuf);
#endif
