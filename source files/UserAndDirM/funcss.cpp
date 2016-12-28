#include "functions.h"

extern char mainDirectory[MAX_PATH];
extern UserProp* CurUser;

void screen (void)
{

}
int exif(char **arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 2))
        return -1;
}
int cp(char **arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 3))
        return -1;
    return 0;
}
int mv(char **arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 3))
        return -1;
    return 0;
}
int wc(char **arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 2))
        return -1;
    return 0;
}
int diff(char **arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 3))
        return -1;
    return 0;
}
int checkarg (char *name, int argnum, int validarg)
{
    if (argnum != validarg)
    {
        printf("Wrong arguments for the %s command.\n", name);
        printf("Try 'help %s' to get information on the command\n", name);
        return 1;
    }
    return 0;
}
int help (char** arguments, int argnum)
{
    char *path = (char *)malloc (MAX_PATH* sizeof(char));
    if (!GetCurrentDirectory(MAX_PATH, path)) { //saving the pwd of the program
        puts("Error Finding the help.");
        return -1;
    }
    if (!SetCurrentDirectory(mainDirectory)) { //changing the current directory to the main project directory
        puts("Error Finding the help.");
        return -2;
    }
    FILE * helper = fopen("helper.txt", "r"); // helper.txt is in the main directory
    if (!helper)
    {
        puts("Error Finding the help.");
        return -3;
    }
    char *buff = (char *) malloc (400* sizeof(char));
    char comname[13];
    int flag = -1;
    if (argnum == 2) {
        while (!feof(helper)) //browses until the file ends
        {
            fgets (buff, 400, helper); // gets each line
            sscanf(buff, "%s", comname); // the first word in the line is the command name
            if (!strcmp(comname, *(arguments + 1))) // if the command name entered matches the input
            {
                printf("%s\n", buff);
                free(buff);
                flag = 1;
                break;
            }
        }
        if (flag == -1)
        {
            puts ("There is no command with that name.");
            puts("you can use 'help' without any arguments to see a list of all the commands.");
            free(buff);
        }
    }
    else if (argnum == 1){
        while (!feof(helper))
        {
            fgets (buff, 500, helper);
            sscanf(buff, "%s", comname); // prints all of the command names
            printf("%s\n", comname);
        }
        free(buff);
    } else
    {
        printf("Wrong arguments for the help command.\n");
        //printf("Try 'help rm' to get information on the command\n");
        return -1;
    }
    SetCurrentDirectory(path); // gets the current directory back to the starting one
    free(path);
    return 0;
}

int cd (char ** arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 2))
        return -1;
    if (!SetCurrentDirectory(*(arguments + 1)))
    {
        puts("Error changing the directory.");
        return -1;
    }
    return 0;
}
int rm (char** arguments, int argnum)
{
    if (argnum == 3 && strcmp(*(arguments+1), "-r"))
    {
        printf("Wrong arguments for the rm command.\n");
        printf("Try 'help rm' to get information on the command\n");
        return -1;
    }
    else if (argnum == 3 && !strcmp(*(arguments+1), "-r"))
    {
        //delete directory
    }
    else if (argnum == 2)
    {
        if (!DeleteFile(*(arguments+1)))
        {
            if (GetLastError() ==  ERROR_FILE_NOT_FOUND)
            {
                puts("File dosen't exist.");
                return -2;
            }
            if (GetLastError() == ERROR_ACCESS_DENIED)
            {
                puts("Access Denied.");
                return -1;
            }
        }
    }
    return 0;
}
int pwd (char** arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 1))
        return -1;
    char *path = (char *)malloc (MAX_PATH* sizeof(char));
    if (GetCurrentDirectory(MAX_PATH, path)) { //getting pwd using WinAPI
        printf("Current working dir: %s\n", path);
    }
    else {
        puts("Error Getting the Current directory.");
    }
    free (path);
    return 0;
}
int mymkdir (char** arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 2))
        return -1;
    char *curdir = (char *)malloc (MAX_PATH* sizeof(char));
    if (!GetCurrentDirectory(MAX_PATH, curdir))
    {
        puts("Error Getting the Current directory.");
        return -1;
    }
    // making up the directory path with string functions
    char * dirpath = (char *) malloc((strlen(*(arguments+1)) + strlen(curdir) + 1)* sizeof(char));
    strcpy (dirpath, curdir);
    strcat (dirpath, "\\");
    strcat (dirpath, *(arguments+1));
    free(curdir);
    int result = CreateDirectory (dirpath , NULL); //creates the directory using WinAPI
    free (dirpath);
    if (!result)
    {
        puts("Error creating a new directory.");
        if (GetLastError() == ERROR_ALREADY_EXISTS) //checks if already exists
            puts("Directory already exists.");
    }
    return 0;
}
int cat (char** arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 2))
        return -1;
    FILE * source = fopen(*(arguments + 1), "r");
    if (source == NULL)
    {
        puts("File dosen't exist.");
        return -1;
    }
    while (!feof(source))
        printf ("%c", fgetc(source));
    fclose(source);
    return 0;
}
int ls (char** arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 1))
        return -1;
    // Declaration
    DIR *d;
    struct dirent *dir; // struct that keeps the props of dirs and files
    struct stat stbuf; // Getting stat of the files and dirs
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    // Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    d = opendir(".");
    if (d) //if successful
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (stat(dir->d_name, &stbuf) == -1) // save the stat of the file/dir in the stbuf
            {
                puts("Detection Error.");
                return -1;
            }
            if (S_ISDIR(stbuf.st_mode)) // if the stbuf is a dir,
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); //change the color to green
            printf("%s\n", dir->d_name); //print the name
            if (S_ISDIR(stbuf.st_mode))
                SetConsoleTextAttribute(hConsole, saved_attributes); // change the color back to normal
        }

        closedir(d);
    } else
        puts("An Error Occurred.");
    return 0;
}

