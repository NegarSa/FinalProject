#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#endif
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>


#ifndef FINALPROJECTDIR_FUNCTIONS_H
#define FINALPROJECTDIR_FUNCTIONS_H
#endif

#define COMMAND_SIZE 50
#define COMMNUMBER 23
//an array of function names
static char functionsname[][COMMNUMBER] = {
        "su","passwd","createuser","cal","time",
        "clear","exit","history","cd","pwd",
        "mkdir","cat","rm","cp","mv","ls","exif",
        "myeditor","wc","diff","help","game", "chcl"};



struct user {
    int id;
    char username[20];
    char name[20];
    int clearance;
    time_t tAvailable;
    char password[20];
};
typedef struct user UserProp;

extern char mainDirectory[MAX_PATH];
extern UserProp* CurUser;
void SignUpAdmin (void);
void SignIn (void);
int passwd (char** arguments, int argnum);
int createuser (char** arguments, int argnum);
int su (char** arguments, int argnum);
int exif(char **arguments, int argnum);
int chcl (char** arguments, int argnum);
char *getcommand(void);
char **parscommand(char *, int *);
int runcommand (char** arguments, int argnum);
int help (char** arguments, int argnum);
int cd (char** arguments, int argnum);
int pwd (char** arguments, int argnum);
int mymkdir (char** arguments, int argnum);
int ls (char** arguments, int argnum);
int cat (char** arguments, int argnum);
int rm (char** arguments, int argnum);
int cp(char **arguments, int argnum);
int mv(char **arguments, int argnum);
int wc(char **arguments, int argnum);
int diff(char **arguments, int argnum);
int checkarg (char *name, int argnum, int validarg);
void screen (void);

