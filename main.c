#include "main.h"

/*main entry point in the code; creates several variables, prints welcome message, begins loop*/
int main(int argc, char **argv)
{
	char *line;
	char **args;
	int status = 1;

	printf("····························\n: __    __          __     :\n:(_ |__|_ | |   |__|_ | |  :\n:__)|  |__|_|__ |  |__|_|__:\n····························\nBY NTK\n\n");

	do {
		char buf[PATH_MAX + 1];
		char *cwd = getcwd(buf, PATH_MAX + 1);
		printf("$");

		if (argc < 2)
		{
			line = read_line();
			args = parse_line(line);
			status = execute(args);
		}
		else
		{
			FILE * fp;
			line = NULL;
			size_t len = 0;

			fp = fopen(argv[1], "r");
			if (fp == NULL)
			{
				exit(EXIT_FAILURE);
			}

			while (((getline(&line, &len, fp)) != -1) && (status != 0))
			{
				printf("%s", line);
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
