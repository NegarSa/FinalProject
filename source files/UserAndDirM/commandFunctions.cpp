#include "functions.h"

char *getcommand()
{
    int size = COMMAND_SIZE;
    int position = 0;
    char *command = (char *)malloc(sizeof(char)*size);
    if (command == NULL) {
        puts("Allocation Error!");
        return 0;
    }
    int ch;
    while (1)
    {
        ch = getchar();
        if (ch == '\n' || ch == EOF) {
            command[position] = '\0';
            // adding the command to the file for keeping the history *****************notice!
            return command;
        }
        command[position++] = (char)ch;
        if (position >= size) // if the input size is more than the allocated memory
        {
            size += COMMAND_SIZE;
            command = (char *)realloc(command, sizeof(char)*size); // reallocate to fit the current buffer
        }
        if (command == NULL) {
            puts("Allocation Error!");
            return 0;
        }

    }
}
char **parscommand(char *command, int* argnum) {
    char *argument;
    int size = 5;
    char **arguments = (char **)malloc(size*(sizeof(char *)));
    int position = 0;
    argument = strtok(command, " "); // get a pointer to after " " character, splitting the command name
    while (argument != NULL)
    {
        arguments[position++] = argument;
        argument=strtok(NULL, " "); // splitting the arguments
        if (position >= size) {
            size += 5;
            arguments = (char **)realloc(arguments, (sizeof(char *))*size); // reallocation to fit the arguments
        }
    }
    arguments[position] = NULL; // add the '/0'
    *argnum = position;
    return arguments;
}

int cal(char **arguments, int argnum)
{ }
int history(char **arguments, int argnum)
{ }
int myeditor(char **arguments, int argnum)
{ }
int game(char **arguments, int argnum)
{ }
int clear(char **arguments, int argnum)
{ }
int mytime(char **arguments, int argnum)
{ }
int myexit(char **arguments, int argnum)
{
    return 42;
}

int runcommand (char ** arguments, int argnum)
{
    int(*functionpointers[]) (char **, int) = {
            &su, &passwd, &createuser, &cal, &mytime, &clear,
            &myexit, &history, &cd, &pwd, &mymkdir, &cat,
            &rm, &cp, &mv, &ls, &exif, &myeditor, &wc, &diff, &help, &game, &chcl};
    if (arguments[0] == NULL)
        return 0;
    for (int m = 0; m < COMMNUMBER; m++)
        if (!strcmp(arguments[0], functionsname[m]))
            return(*functionpointers[m])(arguments, argnum);
    puts("The command is not valid!");
    return 0;
}