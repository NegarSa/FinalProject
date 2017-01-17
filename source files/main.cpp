#include "functions.h"

char mainDirectory[MAX_PATH];
UserProp* CurUser;

int main (void)
{
    CurUser = NULL; // nobody has signed in
    if (!GetCurrentDirectory((DWORD)MAX_PATH, (LPSTR)mainDirectory)) { //saving the pwd of the program
        puts("Error finding the main directory.");
        return 0;
    }
    FILE * his = fopen("history.txt", "w");
    if (his != NULL)
        fclose(his);
    FILE * U = fopen("users.bin", "rb");
    if (U)
    {
        fclose(U);
        SignIn();
    }else {

        SignUpAdmin();
    }
    Sleep(1000);
    screen();
    char *command; // the whole command
    char **arguments; // an array of pointers to the arguments entered
    int argnum = 0; // the number of the arguments, including the command name
    CONSOLE_SCREEN_BUFFER_INFO pos;
    HANDLE hand = GetStdHandle ( STD_OUTPUT_HANDLE );
    while (1){
        command = getcommand();
        arguments = parscommand(command, &argnum);
        if (runcommand(arguments , argnum) == 42) //runcommand only returns 42 when exit is entered
            break;
        free(command);
        free(arguments);
        GetConsoleScreenBufferInfo(hand, &pos);
        if (pos.dwSize.X == pos.dwCursorPosition.X) //when screen ended
            screen();
    }
    return 0;
}
