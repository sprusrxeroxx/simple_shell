#include "shell.h"

/**
 * interactive_mode - CML interpreter
 *
 * Return: none
 */

void interactive_mode(void)

{
	char *line;
	char **args;
	int status = -1;

	do {
	write(STDOUT_FILENO,"$ ", 2);
	line = read_line();
	args = tokenizer(line);
	status = executor(args);

	free(line);
	free(args);

	if (status >= 0)
	{
		exit (status);
	}
	}while (status == -1);
}
