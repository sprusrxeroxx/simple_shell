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



	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
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
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (-1);
}

