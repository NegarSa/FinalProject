#include "functions.h"

extern char mainDirectory[MAX_PATH];
extern UserProp* CurUser;

void screen (void)
{
    DWORD n;//Number of characters written
    DWORD size;// number of visible characters
    COORD coord = {0};//Top left screen position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    GetConsoleScreenBufferInfo ( h, &csbi );
    // Find the number of characters to overwrite
    size = (DWORD) csbi.dwSize.X * csbi.dwSize.Y;
    // Overwrite the screen buffer with whitespace
    FillConsoleOutputCharacter(h, TEXT(' '), size, coord, &n); //n is output, {num of char actually written}
    GetConsoleScreenBufferInfo(h, &csbi);
    FillConsoleOutputAttribute(h, csbi.wAttributes, size, coord, &n);
    // Reset the cursor to the top left position
    SetConsoleCursorPosition(h, coord);
}
int exif(char **arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 2))
        return -1;
    char *path;
    path = (char *) malloc ((strlen(*(arguments + 1)) + 10) * sizeof(char));
    strcpy(path, *(arguments + 1));
    strncat(path, "PROP.dat", 8);
    FILE * prop = fopen(path, "r");
    while(!feof(prop))
        fputc(fgetc(prop), stdout);
    fclose(prop);
    free (path);
    return 0;
}
int cp(char **arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 3))
        return -1;
    if (!CopyFile(*(arguments + 1), *(arguments + 2), 1))
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
            puts("File not found.");
        else if (GetLastError() == ERROR_ACCESS_DENIED)
            puts("Access Denied.");
        else
            puts("An error occurred.");
        return 99999999;
    }
    else {
        char *path;
        path = (char *) malloc ((strlen(*(arguments + 1)) + 4) * sizeof(char));
        strcpy(path, *(arguments + 1));
        strncat(path, "PROP.dat", 8);
        struct stat check;
        if(stat(path, &check))
        {
            if (!CopyFile(path, *(arguments + 2), 1))
                puts("An error occurred.");
        }
    }
    return 0;
}
int mv(char **arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 3))
        return -1;
    if (!MoveFile(*(arguments + 1), *(arguments + 2)))
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
            puts("File not found.");
        else if (GetLastError() == ERROR_ACCESS_DENIED)
            puts("Access Denied.");
        else
            puts("An error occurred.");
        return 99999999;
    }
    else {
        char *path;
        path = (char *) malloc ((strlen(*(arguments + 1)) + 4) * sizeof(char));
        strcpy(path, *(arguments + 1));
        strncat(path, "PROP.dat", 8);
        struct stat check;
        if(stat(path, &check))
        {
            if (!MoveFile(path, *(arguments + 2)))
                puts("An error occurred.");
        }
    }
    return 0;
}
int wc(char **arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 2))
        return -1;
    FILE *TarFile = fopen(*(arguments + 1), "r");
    char buff = 0;
    int lineCount = 0, charCount = 0, spcCount = 0;
    while (!feof(TarFile))
    {
        buff = (char)fgetc(TarFile);
        if (buff == '\n')
            ++lineCount;
        if (isspace(buff))
            ++spcCount;
        ++charCount;
    }
    fclose(TarFile);
    printf("%35s : %20d\n", "Line Count", lineCount + 1);
    printf("%35s : %20d\n", "Character Count", charCount);
    printf("%35s : %20d\n", "Character Count(without spaces)", charCount - spcCount);
    printf("%35s : %20d\n", "Word Count", spcCount + !(buff == '\n' || buff == ' '));
    return 0;
}
int diff(char **arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 3))
        return -1;
    FILE * file1 = fopen(*(arguments + 1), "rb");
    FILE * file2 = fopen(*(arguments + 2), "rb");
    if (!file1 || !file2)
    {
        puts("There is no file with that name.");
        return -1921;
    }
    char buff1, buff2;
    while (!feof (file1))
    {
        fread(&buff1, sizeof(char), 1, file1);
        fread(&buff2, sizeof(char), 1, file2);
        if (buff1 != buff2)
        {
            puts ("Different.");
            fclose(file1);
            fclose(file2);
            return -1;
        }
    }
    puts ("Same.");
    fclose(file1);
    fclose(file2);
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
    int flag = -1;
    if (argnum == 2) {
        for (int x = 0; x < COMMNUMBER; ++x)
        {
            if (strcmp(*(arguments + 1), functionsname[x]) == 0)
            {
                printf("%s\n", functionshelp[x]);
                flag = 0;
            }
        }
            if (flag == -1)
        {
            puts ("There is no command with that name.");
            puts("you can use 'help' without any arguments to see a list of all the commands.");
        }
    }
    else if (argnum == 1){
        for (int x = 0; x < COMMNUMBER; ++x)
            printf("%s\n", functionsname[x]);
    } else
    {
        printf("Wrong arguments for the help command.\n");
        return -1;
    }

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
void delDirRec (DIR *name)
{
    struct dirent *dir; // struct that keeps the props of dirs and files
    struct stat stt; // Getting stat of the files and dirs
    if (name) //if not null
    {
        while ((dir = readdir(name)) != NULL)
        {
            if (stat(dir->d_name, &stt) == -1) // save the stat of the file/dir in the stt
            {
                puts("Detection Error.");
                return;
            }
            if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
                continue;
            if (S_ISDIR(stt.st_mode)) // if the stt is a dir,
            {
                closedir(name);
                DIR *newdir = opendir(dir->d_name);
                if (!RemoveDirectory(dir->d_name)) //if it failed the directory is not empty
                {
                    delDirRec(newdir);
                    RemoveDirectory(dir->d_name);
                }
            }
            else
                if (!DeleteFile(dir->d_name))
                    if (GetLastError() == ERROR_ACCESS_DENIED)
                        puts("Access Denied.");
        }
        closedir(name);
    } else
        puts("An Error Occurred.");
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
        DIR *now = opendir(".");
        delDirRec(now);
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
        else {
            char *path;
            path = (char *) malloc ((strlen(*(arguments + 1)) + 4) * sizeof(char));
            strcpy(path, *(arguments + 1));
            strncat(path, "PROP.dat", 8);
            struct stat check;
            if(stat(path, &check))
            {
                if (!DeleteFile(path))
                    puts("An error occurred.");
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

int expp (char** arguments, int argnum, int place)
{
    if (argnum - place != 2)
    {
        printf("Wrong arguments for the > or >> command.\n");
        printf("Try 'help > or help >>' to get information on the command\n");
        return -1;
    }
    struct stat st1, st2;
    int result2 = stat(*(arguments + place + 1), &st2);
    if (result2 != 0)
    {
        printf("Wrong arguments for the > or >> command.\n");
        printf("Try 'help > or help >>' to get information on the command\n");
        return -1;
    }
    if (place == 1) {
        int result1 = stat(*(arguments), &st1);
        if (result1 == 0) {
            FILE *file1 = fopen(*arguments, "r");
            FILE *file2 = fopen(*(arguments + 2), strcmp(*(arguments + 1), ">>") == 0 ? "a" : "w");
            while (1) {
                fputc(fgetc(file1), file2);
                if (feof(file1))
                    break;
            }
            return 0;
        }
        else {
            FILE *file2 = fopen(*(arguments + place + 1), strcmp(*(arguments + 1), ">>") == 0 ? "a" : "w");
            int i = 0;
            for (int j = 0; j < place ; ++j) {
                fputc(*(arguments+j)[i], file2);
                if (i > strlen(*arguments))
                    break;
            }
            return 0;
        }
    }
    return 0;
}
