#include "main.h"
/*
 *
 */

int main(void) {
    char command[120];

    while (true) {
        show_prompt();
        parse_command(command, sizeof(command));
        execute_command(command);
    }





    

    return 0;
}

