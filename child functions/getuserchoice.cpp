#include <stdio.h>
#include <windows.h>
#include<conio.h>
HANDLE wHnd;
HANDLE rHnd;
void titledim(int, int);
int main(int argn, char **arg) {
	titledim(90, 15);
	printf("\n\n\n");
	for (int i = 0; i < 5; i++)
		printf(" ");
	if (arg[1] != NULL)
		printf(arg[1]);
	else
		puts("No massage!!!");
	char ch[50];
	for (int i = 0; i < 5; i++)
		printf(" ");
	fgets(ch, 50, stdin);
	FILE *fptr;
	fptr = fopen("userchoice.txt", "w");
	fprintf(fptr, "%s", ch);
	fclose(fptr);
	return 0;
}
void titledim(int width, int height) {

	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleTitle(L"Print massage...");

	SMALL_RECT windowSize = { 0, 0, width, height };
	SetConsoleWindowInfo(wHnd, 1, &windowSize);

	COORD bufferSize = { 10, 10 };
	SetConsoleScreenBufferSize(wHnd, bufferSize);

}