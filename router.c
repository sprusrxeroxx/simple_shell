#include "main.h"

/*launches a program using fork and exec and then immediately returns to the shell prompt*/
int launch_no_wait(char **args)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if ((execvp(args[0], args)) == -1)
		{
			perror("1Program invocation has failed");
		}

		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Forking has failed");
	}
	else
	{
		return (1);
	}
	return (0);
}

/*launches a program using fork and exec, waits for the child process to finish, */
int redirection(char **args)
{
	pid_t pid;
	int status = 0;

	int i, j = 0, k = 0, l = 0, input = 0, output = 0, append = 0, fargs = 1;

	for (i = 0; args[i] != NULL; i++)
	{
		if (strcmp("<", args[i]) == 0)
		{
			input = 1;
			j = i;
		}
		else if (strcmp(">", args[i]) == 0)
		{
			output = 1;
			k = i;
		}
		else if (strcmp(">>", args[i]) == 0)
		{
			append = 1;
			l = i;
		}
	}

	pid = fork();
	if (pid == 0)
	{
		if (input)
		{
			int fd0;
			if ((fd0 = open(args[j + 1], O_RDONLY)) < 0)
			{
				perror("error opening file for reading\n");
				fargs = 0;
			}

			dup2(fd0, STDIN_FILENO);
			close(fd0);
		}

		if (output)
		{
			int fd1;
			if ((fd1 = open(args[k + 1], O_RDWR | O_CREAT | O_TRUNC, 0666)) < 0)
			{
				perror("error opening file for writing\n");
				fargs = 0;
			}

			dup2(fd1, STDOUT_FILENO);
			close(fd1);
		}

		if (append)
		{
			int fd1;
			if ((fd1 = open(args[l + 1], O_RDWR | O_CREAT | O_APPEND, 0666)) < 0)
			{
				perror("error opening file for writing\n");
				fargs = 0;
			}

			dup2(fd1, STDOUT_FILENO);
			close(fd1);
		}

		if (fargs)
		{
			if (input)
			{
				char *args2[2];
				strncpy(args[2], args2[0], strlen(args[2]));
				args2[1] = '\0';
				if ((execvp(args[0], args2)) == -1)
				{
					perror("2Program invocation has failed");
				}
			}
			else
			{
				if ((execvp(args[0], args)) == -1)
				{
					perror("3Program invocation has failed");
				}
			}
		}

		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Forking has failed");
	}
	else
	{
		do { 	waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}

/*launches a program using fork and exec, handles pipes for two commands with no arguments*/
int pipes(char **args)
{
	int fd[2];
	pid_t pid;

	int i, j = 0;
	for (i = 0; args[i] != NULL; i++)
	{
		if (strcmp("|", args[i]) == 0)
		{
			j = i;
		}
	}

	if (pipe(fd) == -1)
	{
		perror("pipe error\n");
		return (EXIT_FAILURE);
	}

	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);

		close(fd[0]);
		close(fd[1]);

		if ((execlp(args[j - 1], args[j - 1], NULL)) == -1)
		{
			perror("4Program invocation has failed");
		}

		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Forking has failed");
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[0], STDIN_FILENO);

			close(fd[1]);
			close(fd[0]);

			if ((execlp(args[j + 1], args[j + 1], NULL)) == -1)
			{
				perror("5Program invocation has failed");
			}
		}
		else if (pid < 0)
		{
			perror("Forking has failed");
		}
	}

	close(fd[0]);
	close(fd[1]);
	return (1);
}

