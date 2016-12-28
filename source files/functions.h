#include"definitions.h"
//functions to interpret and run commands
char *getcommand();
char **parscommand(char *, int *);
int runcommand(char **, int);
//functions to excecute the commands
int su(char **arguments, int argnum);
int passwd(char **arguments, int argnum);
int createuser(char **arguments, int argnum);
int cal(char **arguments, int argnum);
int time(char **arguments, int argnum);
int clear(char **arguments, int argnum);
int exit(char **arguments, int argnum);
int history(char **arguments, int argnum);
int cd(char **arguments, int argnum);
int pwd(char **arguments, int argnum);
int mkdir(char **arguments, int argnum);
int cat(char **arguments, int argnum);
int rm(char **arguments, int argnum);
int cp(char **arguments, int argnum);
int mv(char **arguments, int argnum);
int ls(char **arguments, int argnum);
int exif(char **arguments, int argnum);
int myeditor(char **arguments, int argnum);
int wc(char **arguments, int argnum);
int diff(char **arguments, int argnum);
int help(char **arguments, int argnum);
int game(char **arguments, int argnum);

//end of the functions to excecute commands
