#include"variables.h"
#include "functions.h"

HANDLE wHnd;
HANDLE rHnd;
int field[40][20];
int position[20];
int begin;
int flag;
int i;
int timeconst = 50;
int point;
int maxpoint;
int passed;
//move the cursor position to x and y
void gotoxy(int x, int y)
{

	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;

}
//clears the screen
void clearscreen()
{

	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };    // home for the cursor 
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	// Get the number of character cells in the current buffer. 

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.

	if (!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten))
		return;

	// Get the current text attribute.

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;

	// Set the buffer's attributes accordingly.

	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten))
		return;

	// Put the cursor at its home coordinates.

	SetConsoleCursorPosition(hConsole, coordScreen);

}
//generate hurdle
void hurdle()
{
	int x;
	x = rand() % (20);
	x = x / 2 * 2;
	field[0][x] = 'b';
	if (x < 19)field[0][x + 1] = 'b';
	flag = 0;
}
//printing the game
void print()
{
	gotoxy(0, 0);
	printf("max point is: %d\n", maxpoint);
	printf("time: %d\n", passed);
	printf("total points : %d", point);

	for (int i = 0; i < HEIGHT + 1; i++)
	{
		puts("");
		gotoxy(WIDTH - 1, i);
		printf("%c", 176);
		gotoxy(WIDTH * 2 + 1, i);
		printf("%c", 176);

	}
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{

			if (field[i][j] == 'b')
			{
				gotoxy(j + 20, i + 1);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_INTENSITY);
				printf(" ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
			}

		}
	for (int j = 0; j < WIDTH; j++)
	{

		if (position[j] == 'c')
		{
			gotoxy(j + 20, HEIGHT);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			printf(" ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
		}

	}

}
void titledim(int width, int height) {

	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleTitle(L"game...");

	SMALL_RECT windowSize = { 0, 0, width, height };
	SetConsoleWindowInfo(wHnd, 1, &windowSize);

	COORD bufferSize = { 10, 10 };
	SetConsoleScreenBufferSize(wHnd, bufferSize);

}
void downshift()
{
	for (int i = 0; i < 20; i++)
		for (int j = 39; j > 0; j--)
		{
			field[j][i] = field[j - 1][i];
		}
	for (int i = 0; i < 20; i++)
		field[0][i] = 0;
}
void timeflag() {

	if (passed < 5) {
		if (i >= HEIGHT)
		{
			flag = 1;
			i = 0;
		}
		return;
	}
	if (passed < 10) {
		if (i >= HEIGHT / 2)
		{
			flag = 1;
			i = 0;
		}
		return;
	}
	if (passed < 15) {
		if (i >= HEIGHT / 3)
		{
			flag = 1;
			i = 0;
		}
		return;
	}
	if (passed < 20) {
		if (i >= HEIGHT / 4)
		{
			flag = 1;
			i = 0;
		}
		return;
	}

	if (passed > 20) {
		if (i >= HEIGHT / 5)
		{
			flag = 1;
			i = 0;
		}
		return;
	}
}
int  check()
{
	for (int j = 0; j < 19; j++)
		if ((position[j] == 'c'&&field[HEIGHT - 1][j] == 'b') ||
			(position[j] == 'c'&&field[HEIGHT - 2][j] == 'b'))
			return 1;
	return 0;
}
int exit() {

	time_t mytime;
	mytime = time(NULL);
	FILE * fptr;
	fptr = fopen("scores.txt", "a");
	fprintf(fptr, "%d  %s\n", point, ctime(&mytime));
	fclose(fptr);
	showpoints();
	int ch;
	printf("\n\ndo you want play again?\n press 'y' for yes and any other key for no\n");
	ch = getch();
	if (ch != 'y' && ch != 'Y')
		return 1;
	return 0;
}
void showpoints()
{
	clearscreen();
	gotoxy(0, 0);
	char a[100];
	FILE * fptr;
	fptr = fopen("scores.txt", "r");
	while (!feof(fptr))
	{
		fgets(a, 100, fptr);
		if (a[0] != '\n')
			printf("score: %s", a);
	}
	fclose(fptr);
	int ch;
	printf("\n\ndo you want to clear the record?\n press 'y' for yes and any other key for no\n");
	ch = getch();
	if (ch == 'y' || ch == 'Y')
	{
		FILE *fptr;
		fptr = fopen("scores.txt", "w");
		fclose(fptr);
		puts("Done!!!");
	}
}
void findmax()
{
	char s[100];
	char *r;
	long int temp;
	FILE *fptr;
	fptr = fopen("scores.txt", "r");
	if (fptr == NULL)
	{
		maxpoint = 0;
		return;
	}
	while (!feof(fptr))
	{
		fgets(s, 100, fptr);
		temp = strtol(s, &r, 0);
		if (temp > maxpoint)
			maxpoint = temp;
	}
	fclose(fptr);
}