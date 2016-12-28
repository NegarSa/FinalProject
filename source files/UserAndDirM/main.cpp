#include "functions.h"

char mainDirectory[MAX_PATH];
UserProp* CurUser;

int main (void)
{
    CurUser = NULL; // nobody has signed in
    if (!GetCurrentDirectory(MAX_PATH, mainDirectory)) { //saving the pwd of the program
        puts("Error finding the main directory.");
        return 0;
    }
    screen();
    FILE * U = fopen("users.bin", "r");
    fseek(U, 0, SEEK_END);
    int cc = ftell(U);
    fclose(U);
    if (!cc)
        SignUpAdmin();
    else
        SignIn();
    screen();
    char *command; // the whole command
    char **arguments; // an array of pointers to the arguments entered
    int argnum = 0; // the number of the arguments, including the command name
    while (1){
        command = getcommand();
        arguments = parscommand(command, &argnum);
        if (runcommand(arguments , argnum) == 42) //runcommand only returns 42 when exit is entered
            break;
        free(command);
        free(arguments);
    }
    return 0;
}
