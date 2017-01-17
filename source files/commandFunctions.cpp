#include "functions.h"


#define TRUE    1
#define FALSE   0

#define MAX_CMD_LEN  128
#define HISTORY_COUNT 70




int days_in_month[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
char *months[] =
        {
                " ",
                "\n\n\nJanuary",
                "\n\n\nFebruary",
                "\n\n\nMarch",
                "\n\n\nApril",
                "\n\n\nMay",
                "\n\n\nJune",
                "\n\n\nJuly",
                "\n\n\nAugust",
                "\n\n\nSeptember",
                "\n\n\nOctober",
                "\n\n\nNovember",
                "\n\n\nDecember"
        };

void cal();
void historyshell();

int inputyear(void)// the current year for example 2016 nowadays
{
    int year;



    SYSTEMTIME str_t;
    GetSystemTime(&str_t);
    year = str_t.wYear;
    return year;
}

int determinedaycode(int year)//formula to figure out the day
{
    int daycode;
    int d1, d2, d3;

    d1 = (year - 1.) / 4.0;
    d2 = (year - 1.) / 100.;
    d3 = (year - 1.) / 400.;
    daycode = (year + d1 - d2 + d3) % 7;
    return daycode + 1;
}


int determineleapyear(int year)// determine leapyear
{
    if (year % 4 == FALSE && year % 100 != FALSE || year % 400 == FALSE)
    {
        days_in_month[2] = 29;
        return TRUE;
    }
    else
    {
        days_in_month[2] = 28;
        return FALSE;
    }
}

void calendar(int year, int daycode)// the main calender function to indicate the current calender of pc
{
    int month, day;
    SYSTEMTIME str_t;
    GetSystemTime(&str_t);
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    if (1)
    {
        int a = timeinfo->tm_mon + 1;
        if (a == 1)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0df);
        printf("January ");
        if (a == 2)
            printf("February ");
        if (a == 3)
            printf("March ");
        if (a ==4)
            printf("April ");
        if (a == 5)
            printf("May ");
        if (a == 6)
            printf("June ");
        if (a == 7)
            printf("July ");
        if (a == 8)
            printf("August ");
        if (a == 9)
            printf("September ");
        if (a == 10)
            printf("October ");
        if (a == 11)
            printf("November ");
        if (a == 12)
            printf("December ");

        printf("%d ", timeinfo->tm_year + 1900);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0fd);
        printf("\nSat  Sun  Mon  Tue  Wed  Thu  Fri  \n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
        printf("---  —-  —-  —-  —-  —-  —- \n");

        for (day = 1; day <= 1 + daycode * 5; day++)
        {
            printf(" ");
        }


        for (day = 1; day <= days_in_month[str_t.wMonth]; day++)
        {
            printf("%2d", day);
            if (timeinfo->tm_mday == day + 1) {
                HANDLE  hConsole;
                int k =5;

                hConsole = GetStdHandle(STD_OUTPUT_HANDLE);



                SetConsoleTextAttribute(hConsole, k);


            }
            if (timeinfo->tm_mday == day) {
                HANDLE  hConsole;
                int k = 7;

                hConsole = GetStdHandle(STD_OUTPUT_HANDLE);



                SetConsoleTextAttribute(hConsole, k);


            }

            if ((day + daycode) % 7 > 0)
                printf("   ");
            else
                printf("\n ");

        }

        daycode = (daycode + days_in_month[str_t.wMonth]) % 7;
    }
}
void cal() {

    int year, daycode, leapyear;

    year = inputyear();

    daycode = determinedaycode(year);

    determineleapyear(year);

    calendar(year, daycode);

    printf("\n");


}
void openexe(char *command, char *msg)
{
    size_t size = strlen(command);
    wchar_t* wArr = (wchar_t *)malloc(sizeof(wchar_t)*size);
    int i;
    for (i = 0; i < size; ++i)
        wArr[i] = command[i];
    wArr[i] = '\0';
    wchar_t* wArr2;
    if (msg != NULL)
    {
        size_t size2 = strlen(msg);
        wArr2 = (wchar_t *)malloc(sizeof(wchar_t)*size2);
        for (i = 0; i < size2; ++i)
            wArr2[i] = msg[i];
        wArr2[i] = '\0';
    }
    else
        wArr2 = NULL;
    SHELLEXECUTEINFO rSEI = { 0 };
    rSEI.cbSize = sizeof(rSEI);
    rSEI.lpVerb = (LPCSTR)L"open";
    rSEI.lpFile =(LPCSTR) wArr;

    rSEI.lpParameters =(LPCSTR) wArr2;
    rSEI.nShow = SW_NORMAL;
    rSEI.fMask = SEE_MASK_NOCLOSEPROCESS;

    ShellExecuteEx(&rSEI);   // you should check for an error here
    while (TRUE) {
        DWORD nStatus = MsgWaitForMultipleObjects(
                1, &rSEI.hProcess, FALSE,
                INFINITE, QS_ALLINPUT   // drop through on user activity
        );
        if (nStatus == WAIT_OBJECT_0) {  // done: the program has ended
            break;
        }
        MSG msg;     // else process some messages while waiting...
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            DispatchMessage(&msg);
        }
    }  // launched process has exited

    DWORD dwCode;
    GetExitCodeProcess(rSEI.hProcess, &dwCode);  // ERRORLEVEL value
    return;
}
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
{
    cal();
}
int history(char **arguments, int argnum)
{
    FILE *ptr;
    int ch;
    ptr = fopen("history.txt", "r");
    if (ptr == NULL)
        return 0;
    while (!feof(ptr))
    {
        ch = fgetc(ptr);
        printf("%c", ch);
    }
    fclose(ptr);
    puts("");
    return 0;
}
int myeditor(char **arguments, int argnum)
{
    openexe("editor.exe", *(arguments+1));
    FILE * fo = fopen("filename.txt", "r");
    char filename[20];
    fscanf(fo, "%s", filename);
    fclose(fo);
    char *path2;
    path2 = (char *) malloc ((strlen(*(arguments + 1)) + 10) * sizeof(char));
    strcpy(path2, *(arguments + 1));
    strncat(path2, ".PROP.bin", 9);
    FILE * prop = fopen(path2, "wb");
    File f1;
    f1.clearance = CurUser->clearance;
    strncpy(f1.username, CurUser->username, sizeof(CurUser->username));
    time_t raw = time(0);
    struct tm * timenow = localtime(&raw);
    f1.last = *timenow;
    fwrite(&f1, sizeof(File), 1, prop);
    fclose(prop);
    free(path2);
}


int game(char **arguments, int argnum)
{
    openexe("game.exe", *(arguments+1));
    return 0;
}
int clear(char **arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 1)) //it's wrong
        return -1;
    screen();
    return 0;
}
int mytime(char **arguments, int argnum)
{
    printf("Time :%s\n", __TIME__);
}
int myexit(char **arguments, int argnum)
{
    if (checkarg(*arguments, argnum, 1)) //it's wrong
        return -1;
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
    char *path = (char *)malloc (MAX_PATH* sizeof(char));
    if (!GetCurrentDirectory((DWORD)MAX_PATH, (LPSTR)path)) { //saving the pwd of the program
        puts("Error finding the main directory.");
        return 0;
    }
    if (!SetCurrentDirectory(mainDirectory)) { //changing the current directory to the main project directory
        puts("Error Finding the history's database.");
        return 0;
    }
    FILE * history = fopen("history.txt", "a");
    for (int i = 0; i < argnum; ++i)
    {
        fprintf(history, "%s", *(arguments + i));
    }
    fprintf(history, "%c", '\n');
    fclose(history);
    if (!SetCurrentDirectory(path)) { //changing the current directory to the main project directory
        puts("Error Finding the history's database.");
        return 0;
    }
    free(path);
    for (int i = 0; i < argnum; ++i)
    {
        if (strcmp(arguments[i], ">>") == 0 || strcmp(arguments[i], ">") == 0) {
            expp(arguments, argnum, i);
            return 0;
        }
    }
    for (int m = 0; m < COMMNUMBER; m++)
        if (!strcmp(arguments[0], functionsname[m]))
            return(*functionpointers[m])(arguments, argnum);

    if (strcmp((*arguments + 1), "user") == 0 && strcmp((*arguments), "create") == 0 )
        return (*functionpointers[2])(arguments, argnum);
    puts("The command is not valid!");
    return 0;
}