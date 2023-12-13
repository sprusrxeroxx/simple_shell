#include "main.h"

/*
 * IMPORTANT LOOP FUNCTIONS
 * INCLUDES THE FOLLOWING:
 * READLINE, PARSELINE, EXECUTE, LAUNCH
 */



//reads and returns the line of text entered by the user from stdin
char *read_line(void) {
    //declare the string to store the line
    char *line = NULL;
    ssize_t bufsize = 0;
    //getline allocates a buffer
    getline(&line, &bufsize, stdin);
    return line;
}

//parses the line and returns the array of tokens which will be used as arguments
char **parse_line(char *line) {
    //declaration of variables used for storing the separate pieces of the command line
    int bufsize = TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof (char*));
    char *token, **tokens_backup;

    //error check allocation
    if (!tokens) {
        fprintf(stderr, "Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }

    //get the first token from the line
    token = strtok(line, DELIMITERS);
    //cycle through collecting the rest of the tokens
    while (token != NULL) {
        tokens[position] = token;
        position++;

        //reallocate memory in case there are more tokens than space
        if (position >= bufsize) {
            bufsize += TOK_BUFSIZE;
            tokens_backup = tokens;
            tokens = realloc(tokens, bufsize * sizeof (char*));
            if (!tokens) {
                free(tokens_backup);
                fprintf(stderr, "Error allocating memory.\n");
                exit(EXIT_FAILURE);
            }
        }

        //temporary store the next token
        token = strtok(NULL, DELIMITERS);
    }
    //set the final token to null to indicate the termination
    tokens[position] = NULL;
    return tokens;
}

