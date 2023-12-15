#include "main.h"

/**
 * tokenizer - cut string into parts
 * @line: string to cut
 *
 * Return: pointer
 */

char **tokenizer(char *line)
{
	int bufsize = 64;
	int i = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		write(STDERR_FILENO, "allocation error in tokenizer: token\n", 36);
		exit(EXIT_FAILURE);
	}
	token = strtok(line, TOK_DELIM);
	while (token != NULL)
	{
		if (token[0] == '#')
		{
			break;
		}
		tokens[i] = token;
		i++;
		if (i >= bufsize)
		{
			bufsize += bufsize;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				write(STDERR_FILENO, "reallocation error in tokenizer: tokens", 38);
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[i] = NULL;
	return (tokens);
}

