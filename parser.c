#include "main.h"

/*
 *IMPORTANT LOOP FUNCTIONS
 *INCLUDES THE FOLLOWING:
 *READLINE, PARSELINE, EXECUTE, LAUNCH
 */

char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	getline(&line, &bufsize, stdin);
	return (line);
}

/*parses the line and returns the array of tokens which will be used as arguments*/
char **parse_line(char *line)
{
	unsigned int  bufsize = TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize* sizeof(char*));
	char *token, **tokens_backup;

	if (!tokens)
	{
		fprintf(stderr, "Error allocating memory.\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, DELIMITERS);

	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens_backup = tokens;
			tokens = realloc(tokens, bufsize* sizeof(char*));
			if (!tokens)
			{
				free(tokens_backup);
				fprintf(stderr, "Error allocating memory.\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, DELIMITERS);
	}

	tokens[position] = NULL;
	return (tokens);
}
