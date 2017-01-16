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
char **parscommand(char *command, int * argnum) {
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
	*argnum = position;
	return arguments;
}
int runcommand(char **arguments, int argnum)
{
	int(*functionpointers[]) (char **, int) = {
		&su,&passwd,&createuser,&cal,&time,&clear,
		&exit,&history,&cd,&pwd,&mkdir,&cat,
		&rm,&cp,&mv,&ls,&exif,&myeditor,&wc,&diff,&help,&game, };
	if (arguments[0] == NULL)
		return 0;
	for (int m = 0; m < COMMNUMBER; m++)
		if (!strcmp(arguments[0], functionsname[m]))
			return(*functionpointers[m])(arguments, argnum);
	puts("the command is not valid!!!");
	return 0;
}
//......

void popenexe(char *command, char *msg)
{
	size_t size = strlen(command);
	wchar_t* wArr = new wchar_t[size];
	int i;
	for (i = 0; i < size; ++i)
		wArr[i] = command[i];
	wArr[i] = '\0';
	wchar_t* wArr2;
	if (msg != NULL)
	{
		size_t size2 = strlen(msg);
		wArr2 = new wchar_t[size2];
		for (i = 0; i < size2; ++i)
			wArr2[i] = msg[i];
		wArr2[i] = '\0';
	}
	else
		wArr2 = NULL;
	SHELLEXECUTEINFO rSEI = { 0 };
	rSEI.cbSize = sizeof(rSEI);
	rSEI.lpVerb = L"open";
	rSEI.lpFile = wArr;

	rSEI.lpParameters = wArr2;
	rSEI.nShow = SW_NORMAL;
	rSEI.fMask = SEE_MASK_NOCLOSEPROCESS;

	ShellExecuteEx(&rSEI);   // you should check for an error here
	while (TRUE) {
		DWORD nStatus = MsgWaitForMultipleObjects(
			1, &rSEI.hProcess, FALSE,
			INFINITE, QS_ALLINPUT   // drop through on user activity 
			);
		if (nStatus == WAIT_OBJECT_0) {  // done: the program has ended
			break;
		}
		MSG msg;     // else process some messages while waiting...
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			DispatchMessage(&msg);
		}
	}  // launched process has exited

	DWORD dwCode;
	GetExitCodeProcess(rSEI.hProcess, &dwCode);  // ERRORLEVEL value
	return;
}
//functions to run commands
int su(char **arguments, int argnum)
{
	puts("su");
	return 0;
}
int passwd(char **arguments, int argnum)
{
	puts("passwd");
	return 0;
}
int createuser(char **arguments, int argnum)
{
	puts("createuser");
	return 0;
}
int cal(char **arguments, int argnum)
{
	puts("cal");
	return 0;
}
int time(char **arguments, int argnum)
{
	puts("time");
	return 0;
}
int clear(char **arguments, int argnum)
{
	puts("clear");
	return 0;
}
int exit(char **arguments, int argnum)
{
	puts("exit");
	return 0;
}
int history(char **arguments, int argnum)
{
	puts("history");
	return 0;
}
int cd(char **arguments, int argnum)
{
	puts("cd");
	return 0;
}
int pwd(char **arguments, int argnum)
{
	puts("pwd");
	return 0;
}
int mkdir(char **arguments, int argnum)
{
	puts("mkdir");
	return 0;
}
int cat(char **arguments, int argnum)
{
	puts("cat");
	return 0;
}
int rm(char **arguments, int argnum)
{
	puts("rm");
	return 0;
}
int cp(char **arguments, int argnum)
{
	puts("cp");
	return 0;
}
int mv(char **arguments, int argnum)
{
	puts("mv");
	return 0;
}
int ls(char **arguments, int argnum)
{
	puts("ls");
	return 0;
}
int exif(char **arguments, int argnum)
{
	puts("exif");
	return 0;
}
int wc(char **arguments, int argnum)
{
	puts("wc");
	return 0;
}
int diff(char **arguments, int argnum)
{
	puts("diff");
	return 0;
}
int help(char **arguments, int argnum)
{
	puts("help");
	return 0;
}
int myeditor(char **arguments, int argnum)
{
	popenexe("editor.exe", arguments[1]);
	return 0;
}
int game(char **arguments, int argnum)
{
	popenexe("game.exe", arguments[1]);
	return 0;
}