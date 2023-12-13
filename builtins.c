#include "main.h"

/*
 *INTERNAL FUNCTIONS
 *INCLUDES THE FOLLOWING:
 *CD, CLR, DIR, _ENVIRON, ECHO, HELP, _PAUSE, QUIT
 */

/*internal function cd, changes directory to args[1] or if no arguments given it prints the current directory*/
int cd(char **args)
{
	char cwd[1024];

	if (args[1] == NULL){
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			printf("No directory given as an argument.\nThe current working directory is: %s\n", cwd);
		}
		else
		{
			perror("getcwd() error.");
		}
	}
	else
	{

		if (chdir(args[1]) != 0)
		{
			perror("Error changing directory");
		}

		/*gets the new directory and sets the environment variable PWD to it*/
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			setenv("PWD", cwd, 1);
		}
	}

	return 1;
}

/*internal function clr, clears the terminal screen by using an ANSI escape sequence*/
int clr(void)
{
	/*this specific escape sequence moves all text to above the top line of the terminal*/
	printf("\033[1;1H\033[2J");
	return (1);
}

/*internal function dir, prints out the contents of the given directory similar to the ls command*/
int dir(char **args)
{
	/*struct used to access the directory*/
	DIR * dp;
	struct dirent * ep;

	if (args[1] == NULL)
	{
		/*no argument given, prints out the current working directory*/
		char buf[PATH_MAX + 1];
		char *cwd = getcwd(buf, PATH_MAX + 1);
		printf("No directory given as an argument.\nThe current working directory is: %s\n", cwd);
		dp = opendir(cwd);
	}
	else
	{
		/*open the directory argument*/
		dp = opendir(args[1]);
	}

	if (dp != NULL)
	{
		/*cycles through the elements in the directory and prints them out*/
		while ((ep = readdir(dp)))
		{
			puts(ep->d_name);
		}

		(void) closedir(dp);
	}
	else

	{
		perror("Couldn't open the directory");
	}

	return 1;
}

/*internal function _environ, prints out all of the environment variables*/
int env(void)
{
	int i;
	/*uses the extern char to gain access to the environment variables*/
	char *s = *environ;

	/*cycles through and prints out each environment variable one per line*/
	for (i = 1; s; i++)
	{
		printf("%s\n", s);
		s = *(environ + i);
	}

	return 1;
}

/*internal function echo, prints out the string of arguments given after the echo command*/
int echo(char **args)
{
	int i = 1;
	/*cycles through all arguments after echo and prints them out*/
	while (args[i] != NULL)
	{
		printf("%s ", *(args + i));
		i++;
	}

	printf("\n");
	return 1;
}

/*internal function help, brings up the instructions for using my shell*/
int help(void)
{
	/*declaration of variables used for opening and displaying the readme
	 *the value of totalLines is specific to the readme included*/
	FILE *fp = NULL;
	int lineCount = 0;
	int totalLines = 100;
	char ch[256];

	/*check the current directory to find and open readme*/
	fp = fopen("./readme", "r");
	if (fp == NULL)
	{
		fputs("Unable to open readme file.", stdout);
		exit(EXIT_FAILURE);
	}

	/*brings up the first 10 lines of the readme, user can request 10 more lines or exit*/
	while (fgets(ch, 256, fp) != NULL)
	{
		lineCount++;
		fputs(ch, stdout);

		/*exit if final line is reached*/
		if (lineCount == totalLines)
		{
			return 1;
		}

		/*stop giving help lines unless requested by user*/
		if (lineCount == 10)
		{
			char c;
			printf("Press 'enter' to read more or press 'q' to quit.\n");
			c = getchar();
			if (c == 'q')
			{
				return 1;
			}
			else
			{
				lineCount = 0;
			}
		}
	}

	return 1;
}

/*internal function _pause, uses a loop and getchar to wait for user to input "enter" before returning control*/
int _pause(void)
{
	char c;
	/*display pause message*/
	printf("PAUSED\n");
	/*get next character and do nothing until the user presses 'enter'*/
	while ((c = getchar()) != '\n') {}

	return 1;
}

/*internal function quit, returns 0 to status variable which breaks the shell loop*/
int quit(char **args)
{
	/*0 is false, therefore this causes while condition to stop*/
	int exit_code;
	exit_code = atoi(args[1]);
	exit(exit_code);
	return (0);
}

/*internal functions to set and unset environment variables*/

int set_env_var(char **args)
{
	char *new_env = malloc(strlen(args[2]) + strlen(args[3]) + 2);

	if (strlen(args[2]) > MAX_VAR_NAME_LEN || strlen(args[3]) > MAX_VAR_VALUE_LEN)
	{
		fprintf(stderr, "Error: Variable name or value is too long.\n");
		return (1);
	}

	if (!new_env)
	{
		fprintf(stderr, "Error: Memory allocation failed.\n");
		return (1);
	}

	strcpy(new_env, args[2]);
	strcat(new_env, "=");
	strcat(new_env, args[3]);

	if (setenv(args[2], args[3], 1) != 0)
	{
		fprintf(stderr, "Error: Failed to set environment variable '%s'.\n", args[2]);
		free(new_env);
		return (1);
	}

	free(new_env);
	return (0);
}
