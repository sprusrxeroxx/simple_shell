#include "main.h"


//main entry point in the code; creates several variables, prints welcome message, begins loop
int main(int argc, char **argv) {

    //declaration of variables to be used for storing the command line
    char *line;
    char **args;
    int status = 1;

    //prints welcome message
    printf("····························\n: __    __          __     :\n:(_ |__|_ | |   |__|_ | |  :\n:__)|  |__|_|__ |  |__|_|__:\n····························\nBY NTK\n\n");

    //begin run of the loop
    do {
        //gets current directory
        char buf[PATH_MAX + 1];
        char *cwd = getcwd(buf, PATH_MAX + 1);
        printf("$");

        //determines whether a command line argument was passed or not
        if (argc < 2) {
            //no command file
            line = read_line();
            args = parse_line(line);
            status = execute(args);
        } else {
            //given a command file, must open and read lines from the file
            FILE *fp;
            line = NULL;
            size_t len = 0;

            //error check the opening of the file
            fp = fopen(argv[1], "r");
            if (fp == NULL) {
                exit(EXIT_FAILURE);
            }

            //loop through the file and execute each line
            while (((getline(&line, &len, fp)) != -1) && (status != 0)) {
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

    return EXIT_SUCCESS;
}
