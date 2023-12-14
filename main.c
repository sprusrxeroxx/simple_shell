#include "main.h"

/*main entry point in the code; creates several variables, prints welcome message, begins loop*/
int main(int argc, char **argv)
{
	char *line;
	char **args;
	int status = 1;
	char *welcome = "WELCOME TO MY SHELL\nBY NTK\nTHE GATES OF SHELL\n";

	write(STDOUT_FILENO, welcome, strlen(welcome));

	do {
		size_t len = 0;
		FILE * fp;
		const char *prompt = " $";

		write(STDOUT_FILENO, prompt, strlen(prompt));

		if (argc < 2)
		{
			line = read_line();
			args = parse_line(line);
			status = execute(args);
		}
		else
		{
			line = NULL;

			fp = fopen(argv[1], "r");
			if (fp == NULL)
			{
				exit(EXIT_FAILURE);
			}

			while (((getline(&line, &len, fp)) != -1) && (status != 0))
			{
				write(STDOUT_FILENO, line, strlen(line));
				args = parse_line(line);
				status = execute(args);
			}

			status = 0;
			fclose(fp);
		}

		free(line);
		free(args);
	} while (status);

	return (EXIT_SUCCESS);
}

