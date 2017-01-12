#include<stdio.h>
#include<stdlib.h>
void history();
int main()
{
	history();
	return 0;
}
void history()
{
	FILE *ptr;
	int ch;
	ptr = fopen("history.txt", "r");
	if (ptr == NULL)
		return;
	while (!feof(ptr))
	{
		ch = fgetc(ptr);
		printf("%c", ch);
	}
	fclose(ptr);
	puts("");
	return;
}