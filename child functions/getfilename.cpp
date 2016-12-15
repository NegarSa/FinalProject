#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<string.h>
#include<conio.h>
HANDLE wHnd;   
HANDLE rHnd; 
void titledim(int ,int );
int main() {
	titledim(90, 15);
	printf("\n");
	for (int i = 0; i < 12; i++)
		printf(" ");
	printf("Enter the file name with proper prefix \" Example:   file.txt \"\n\n\n");
	for (int i = 0; i < 12; i++)
		printf(" ");
	char string[50];
	FILE *fptr;
	fgets(string, 50, stdin);
	for (int i = strlen(string) - 1; i >= 0; i--)
		if (string[i] == '\n')
			string[i] = '\0';
	fptr = fopen("filename.txt", "w");
	fprintf(fptr, "%s", string);
	fclose(fptr);
	return 0;
}
void titledim( int width,int height) {

	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleTitle(L"reading file name");

	SMALL_RECT windowSize = { 0, 0, width, height };
	SetConsoleWindowInfo(wHnd, 1, &windowSize);

	COORD bufferSize = { 10, 10 };
	SetConsoleScreenBufferSize(wHnd, bufferSize);

}
