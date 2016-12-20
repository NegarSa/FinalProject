#include"definitions.h"
//functions to interpret and run commands
char *getcommand();
char **parscommand(char *);
int runcommand(char **);
//functions to excecute the commands
int su(char **arguments);
int passwd(char **arguments);
int createuser(char **arguments);
int cal(char **arguments);
int time(char **arguments);
int clear(char **arguments);
int exit(char **arguments);
int history(char **arguments);
int cd(char **arguments);
int pwd(char **arguments);
int mkdir(char **arguments);
int cat(char **arguments);
int rm(char **arguments);
int cp(char **arguments);
int mv(char **arguments);
int ls(char **arguments);
int exif(char **arguments);
int myeditor(char **arguments);
int wc(char **arguments);
int diff(char **arguments);
int help(char **arguments);
int game(char **arguments);

//end of the functions to excecute commands