#include "main.h"

/**
 * new_process - creates a new process
 * @args: array of strings and flags
 *
 * Return:1 or 0
 */

int new_process(char **args)
{
	pid_t pid;
	int status;
	char *program_path = args[0];
	char **remaining_args = args + 1;
	int args_count = sizeof(**args) / sizeof(char *);
	


	pid = fork();
	remaining_args[args_count - 1] = NULL;
	if (pid == 0)
	{
		if (execve(program_path, remaining_args, environ) == -1)
		{
			perror("error in new_process: child process");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("error in new_process: forking");
	}
	else
	{
		do{
			waitpid(pid, &status, WUNTRACED);
		}while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (-1);
}

