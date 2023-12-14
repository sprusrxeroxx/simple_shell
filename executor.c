#include "main.h"

/*array containing a list of the internal functions*/
char *internals_str[] = { "cd", "clr", "dir", "env", "echo", "help", "_pause", "exit", "setenv",
};

/*array containing pointers to each of the internal functions*/
int(*internals_func[])(char **) = { &cd, &clr, &dir, &env, &echo, &help, &_pause, &quit, &set_env_var
};

/*returns the total number of internal functions*/
int num_internals()
{
	return (sizeof(internals_str) / sizeof(char*));
}

/*executes either the internal function or launches a program based on the given arguments*/
int execute(char **args)
{
	int i;
	int wait = 0, pipe = 0;

	if (args[0] == NULL)
	{
		return (1);
	}


	for (i = 0; args[i] != NULL; i++)
	{
		if (strcmp("&", args[i]) == 0)
		{
			wait = 1;
		}
		else if (strcmp("|", args[i]) == 0)
		{
			pipe = 1;
		}
	}

	if ((!wait) && (!pipe))
	{
		for (i = 0; i < num_internals(); i++)
		{
			if (strcmp(args[0], internals_str[i]) == 0)
			{
				return (*internals_func[i])(args);
			}
		}
	}

	if (wait)
	{
		return (launch_no_wait(args));
	}
	else if (pipe)
	{
		return (pipes(args));
	}
	else
	{
		return (redirection(args));
	}
}

