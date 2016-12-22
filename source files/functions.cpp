#include"functions.h"
char *getcommand()
{
	int size = COMMAND_SIZE;
	int position = 0;
	char *command = (char *)malloc(sizeof(char)*size);
	if (command == NULL) {
		puts("allocation error!!!!");
		return 0;
	}
	printf("\\");
	int ch;
	while (1)
	{
		ch = getchar();
		if (ch == '\n' || ch == EOF) {
			command[position] = '\0';
			return command;
		}
		command[position++] = ch;
		if (position >= size)
		{
			size += COMMAND_SIZE;
			command = (char *)realloc(command, sizeof(char)*size);
		}
		if (command == NULL) {
			puts("allocation error!!!!");
			return 0;
		}

	}
}
char **parscommand(char *command) {
	char *argument;
	int size = 5;
	char **arguments = (char **)malloc(size*(sizeof(char *)));
	int position = 0;
	argument = strtok(command, " ");
	while (argument != NULL)
	{
		arguments[position++] = argument;
		argument = strtok(NULL, " ");
		if (position >= size) {
			size += 5;
			arguments = (char **)realloc(arguments, (sizeof(char *))*size);
		}
	}
	arguments[position] = NULL;
	return arguments;
}
int runcommand(char **arguments)
{
	int(*functionpointers[]) (char **) = {
		&su,&passwd,&createuser,&cal,&time,&clear,
		&exit,&history,&cd,&pwd,&mkdir,&cat,
		&rm,&cp,&mv,&ls,&exif,&myeditor,&wc,&diff,&help,&game, };
	if (arguments[0] == NULL)
		return 0;
	for (int m = 0; m < COMMNUMBER; m++)
		if (!strcmp(arguments[0], functionsname[m]))
			return(*functionpointers[m])(arguments);
	puts("the command is not valid!!!");
	return 0;
}

//functions to run commands
int su(char **arguments)
{
	puts("su");
	return 0;
}
int passwd(char **arguments)
{
	puts("passwd");
	return 0;
}
int createuser(char **arguments)
{
	puts("createuser");
	return 0;
}
int cal(char **arguments)
{
	puts("cal");
	return 0;
}
int time(char **arguments)
{
	puts("time");
	return 0;
}
int clear(char **arguments)
{
	puts("clear");
	return 0;
}
int exit(char **arguments)
{
	puts("exit");
	return 0;
}
int history(char **arguments)
{
	puts("history");
	return 0;
}
int cd(char **arguments)
{
	puts("cd");
	return 0;
}
int pwd(char **arguments)
{
	puts("pwd");
	return 0;
}
int mkdir(char **arguments)
{
	puts("mkdir");
	return 0;
}
int cat(char **arguments)
{
	puts("cat");
	return 0;
}
int rm(char **arguments)
{
	puts("rm");
	return 0;
}
int cp(char **arguments)
{
	puts("cp");
	return 0;
}
int mv(char **arguments)
{
	puts("mv");
	return 0;
}
int ls(char **arguments)
{
	puts("ls");
	return 0;
}
int exif(char **arguments)
{
	puts("exif");
	return 0;
}
int wc(char **arguments)
{
	puts("wc");
	return 0;
}
int diff(char **arguments)
{
	puts("diff");
	return 0;
}
int help(char **arguments)
{
	puts("help");
	return 0;
}

