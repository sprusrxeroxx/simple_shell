#include "shell.h"

/**
 * executor - checks if cmd is builtin or not
 * @args: command and flags
 *
 * Return: 1 or 0
 */

int executor(char **args)
{
	char *builtin_func_list[] = {
		"cd",
		"env",
		"help",
		"exit"
	};
	int (*builtin_func[])(char **) = {
		&my_cd,
		&my_env,
		&my_help,
		&my_exit
	};
	int i = 0;

	if (args[0] == NULL)
	{
		return (-1);
	}
	for (; i < sizeof(builtin_func_list) / sizeof(char *); i++)
	{
		if (strcmp(args[0], builtin_func_list[i]) == 0)
		{
			return ((*builtin_func[i])(args));
		}
	}
	return (new_process(args));
}
