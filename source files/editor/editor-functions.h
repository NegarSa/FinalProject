#include"editor-definitions.h"
void insert(nodeptr *start, nodeptr position, int value);
void Delete(nodeptr *start, nodeptr position);
void print(nodeptr start, node position);
void setcursor(nodeptr start, node position);
//seeking a char in the list form the current position to the begining and end for 0 and 1 respectively
int seekchar(nodeptr position, int direction, int value,int enable,int *length);
void toleft(nodeptr position);
void toright(nodeptr position);
void goup(nodeptr position);
void godown(nodeptr position);
void readfromfile(nodeptr *start, nodeptr position);
void printtofile(nodeptr start);
void openexe(char *, char *);
void findstring(nodeptr start);
void select(nodeptr start, nodeptr position, int prevchoice,int choice);
void copy(nodeptr start,nodeptr *buffstart,nodeptr buffpos, int prevchoice);
void emptybuff(nodeptr *buffstart);
void paste(nodeptr *start, nodeptr position, nodeptr buffstart);
void clearscreen();