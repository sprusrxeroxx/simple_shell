#include "main.h"



//launches a program using fork and exec and then immediately returns to the shell prompt
int launch_no_wait(char **args) {
    //used to identify child processes
    pid_t pid;

    //create a child process
    pid = fork();
    if (pid == 0) {
        //in the child process, execute the given command
        if ((execvp(args[0], args)) == -1) {
            perror("Program invocation has failed");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        //error occurred with fork
        perror("Forking has failed");
    } else {
        //in the parent process, return to the shell prompt instead of waiting for the child to finish
        return 1;
    }
}

//launches a program using fork and exec, waits for the child process to finish, also handles I/O redirects
int redirection(char **args) {
    //variables for determining child processes
    pid_t pid;
    int status = 0;

    //variables to indicate whether there is redirection and where
    int i, j = 0, k = 0, l = 0, input = 0, output = 0, append = 0, fargs = 1;

    //cycles through the arguments to find any redirection symbols
    for (i = 0; args[i] != NULL; i++) {
        if (strcmp("<", args[i]) == 0) {
            input = 1;
            j = i;
        } else if (strcmp(">", args[i]) == 0) {
            output = 1;
            k = i;
        } else if (strcmp(">>", args[i]) == 0) {
            append = 1;
            l = i;
        }
    }

    //creates a child process
    pid = fork();
    if (pid == 0) {
        //in the child process
        if (input) {
            //change file descriptors from stdin to args[j+1] if redirecting input
            int fd0;
            if ((fd0 = open(args[j + 1], O_RDONLY)) < 0) {
                printf("error opening %s for reading\n", args[j + 1]);
                fargs = 0;
            }
            dup2(fd0, STDIN_FILENO);
            close(fd0);
        }
        if (output) {
            //change file descriptors from stdout to args[k+1] if redirecting output
            int fd1;
            if ((fd1 = open(args[k + 1], O_RDWR | O_CREAT | O_TRUNC, 0666)) < 0) {
                printf("error opening %s for writing\n", args[k + 1]);
                fargs = 0;
            }
            dup2(fd1, STDOUT_FILENO);
            close(fd1);
        }
        if (append) {
            //change file descriptors from stdout to args[l+1] if redirecting output
            int fd1;
            if ((fd1 = open(args[l + 1], O_RDWR | O_CREAT | O_APPEND, 0666)) < 0) {
                printf("error opening %s for writing\n", args[l + 1]);
                fargs = 0;
            }
            dup2(fd1, STDOUT_FILENO);
            close(fd1);
        }
        //check that there were actually arguments passed from redirects
        if (fargs) {
	 if(input){
		char *args2[2];
		strncpy(args[2], args2[0], strlen(args[2]));
		args2[1] = '\0';
            if ((execvp(args[0], args2)) == -1) {
               perror("Program invocation has failed");
            }
	  }else{
		if((execvp(args[0], args)) == -1){
		perror("Program invocation has failed");
	    }
	  }
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        //error occurred with fork
        perror("Forking has failed");
    } else {
        //in the parent process
        do {
            //wait for the child process to finish before returning control of the shell to the user
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

//launches a program using fork and exec, handles pipes for two commands with no arguments
int pipes(char **args) {
    //variables for file descriptors and child processes
    int fd[2];
    pid_t pid;

    //find the position of the pipe
    int i, j = 0;
    for (i = 0; args[i] != NULL; i++) {
        if (strcmp("|", args[i]) == 0) {
            j = i;
        }
    }

    //create the pipe
    if (pipe(fd) == -1) {
        printf("pipe error\n");
        return EXIT_FAILURE;
    }

    //create a child process
    pid = fork();
    if (pid == 0) {
        //in the child process
        //replace standard output with the output half of the pipe
        dup2(fd[1], STDOUT_FILENO);
        //close the unused input half of the pipe
        close(fd[0]);
        close(fd[1]);
        //execute the first program
        if ((execlp(args[j - 1], args[j - 1], NULL)) == -1) {
            perror("Program invocation has failed");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        //error occurred with fork
        perror("Forking has failed");
    } else {
        //in the parent process
        //create another process
        pid = fork();
        if (pid == 0) {
            //in the child process
            //replace standard input with the input half of the pipe
            dup2(fd[0], STDIN_FILENO);
            //close the unused output half of the pipe
            close(fd[1]);
            close(fd[0]);
            //execute the second program
            if ((execlp(args[j + 1], args[j + 1], NULL)) == -1) {
                perror("Program invocation has failed");
            }
        } else if (pid < 0) {
            //error occurred with fork
            perror("Forking has failed");
        }
    }
    //close the file descriptors and return from the parent
    close(fd[0]);
    close(fd[1]);
    return 1;
}
