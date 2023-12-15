#include "main.h"

/**
 * read_stream - read a line
 *
 * Return: pointer
 */

char *read_stream(void)
{
	int bufsize = 1024;
	int i = 0;
	char *line = malloc(sizeof(char) * bufsize);
	int character;

	if (line == NULL)
	{
		write(STDERR_FILENO, "allocation error in read_stream", 32);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		character = getchar();
		if (character == EOF)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		else if (character == '\n')
		{
			line[i] = '\0';
			return (line);
		}
		else
		{
			line[i] = character;
		}
		i++;
		if (i >= bufsize)
		{
			bufsize += bufsize;
			line = realloc(line, bufsize);
			if (line == NULL)

			{
			write(STDERR_FILENO, "reallocation error in read_stream", 34);
			exit(EXIT_FAILURE);
			}
		}
	}
}

