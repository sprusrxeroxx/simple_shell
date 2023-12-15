#include "main.h"

/**
 * no_interactive_mode - CML reader
 *
 * Return: none
 */

void no_interactive_mode(void)
{
	char *line;
	char **args;
	int status = -1;

	do {
		line = read_stream();
		args = tokenizer(line);
		status = executor(args);
		free(line);
		free(args);

		if (status >= 0)
		{
		exit(status);
		}
	} while (status == -1);
}
