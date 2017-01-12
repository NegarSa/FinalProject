#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include<windows.h>
int x, y;
char textofcm[20];
char usercm[20];
char * usercmptr;
int numofset = 0;
int database[100];
int exdatabase[100] = { 0 };
int getusercm();
int main()
{
	while (getusercm() == 1);

}//end main
void showcal(int y, int m);
int isLeap(int y)
{
	return((y % 400 == 0) || (y % 4 == 0 && y % 100 == 0));
}

int start(int y, int m)
{
	int t[] = { 0,3,2,5,0,3,5,1,4,6,2,4 };
	int year = y - (m<3);
	return(y + y / 4 - y / 100 + y / 400 + t[m - 1] + 2) % 7;
}

int totaldays(int y, int m)
{
	switch (m)
	{
	case 2: return isLeap(y) ? 29 : 28;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	default:
		return 31;
	}
}
void showcal(int y, int m)
{
	int i;
	char *mname[] = { "January","Febraury","March","April","May","June","July","August","September","October","NOvember","December" };
	int day, days, dow;
	days = totaldays(y, m);
	dow = start(y, m);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0fd);
	printf("\n%s  %d              ", mname[m - 1], y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0df);
	printf("\nSAT SUN MON TUE WED THU FRI ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
	printf("\n--- --- --- --- --- --- --- \n");
	for (i = 0; i<dow; i++) {
		printf("    ");
	}
	for (day = 1; day <= days; day++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0d);
		printf("%3d ", day);
		if (++dow>6) { dow = 0; printf("\n"); }
	}
	printf("\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);

}
int getusercm()
{
	int flag = 1;
	int i = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf(" Please enter your command! :\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0D);
	fgets(usercm, 100, stdin);
	usercmptr = usercm;
	for (; *usercmptr != '\0'; usercmptr++)
		if (!isdigit(*usercmptr) && *usercmptr != '-')
			textofcm[i++] = tolower(*usercmptr);
	textofcm[i] = '\0';
	i = 0;
	usercmptr = usercm;
	for (int m = strlen(textofcm) - 1; !isalpha(textofcm[m]); m--)
		if (textofcm[m] == ' ' || textofcm[m] == '\t' || textofcm[m] == '\n')
			textofcm[m] = '\0';
	if (strcmp(textofcm, "call") == 0)//call operation************************
	{
		int month;
		time_t now;
		time(&now);
		char string[50];
		sprintf(string, "%s", ctime(&now));
		int year = 0;
		int i = strlen(string) - 2;
		for (int j = 0; j < 4; i--, j++)
		{
			year = (string[i] - '0') * 1000 + year / 10;
		}

		if (string[4] == 'J', string[5] == 'a', string[6] == 'n')
			month = 1;
		if (string[4] == 'F', string[5] == 'e', string[6] == 'b')
			month = 2;
		if (string[4] == 'M', string[5] == 'a', string[6] == 'r')
			month = 3;
		if (string[4] == 'A', string[5] == 'p', string[6] == 'r')
			month = 4;
		if (string[4] == 'M', string[5] == 'a', string[6] == 'y')
			month = 5;
		if (string[4] == 'J', string[5] == 'u', string[6] == 'n')
			month = 6;
		if (string[4] == 'J', string[5] == 'u', string[6] == 'l')
			month = 7;
		if (string[4] == 'A', string[5] == 'u', string[6] == 'g')
			month = 8;
		if (string[4] == 'S', string[5] == 'e', string[6] == 'p')
			month = 9;
		if (string[4] == 'O', string[5] == 'c', string[6] == 't')
			month = 10;
		if (string[4] == 'N', string[5] == 'o', string[6] == 'v')
			month = 11;
		if (string[4] == 'D', string[5] == 'e', string[6] == 'c')
			month = 12;
		showcal(year, month);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
		return 1;
	}//end of set******
	if (strcmp(textofcm, "time") == 0)//time operation**********
	{
		time_t now;
		time(&now);
		char string[50];
		sprintf(string, "%s", ctime(&now));
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
		printf("Time is:");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f5);
		printf("%c%c%c%c%c%c%c%c%c \n", string[10], string[11], string[12], string[13], string[14], string[15], string[16], string[17], string[18]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
		return 1;
	}//end of time****
	if (strcmp(textofcm, "exit") == 0)//exit operation**********
	{
		flag = 0;
		return 0;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
	}//end exit********



}//end getuser cm






