#include"functions.h"

int main()
{
	char *command;
	char **arguments;
	int argnum;
	while (1) {
		command = getcommand();
		arguments = parscommand(command, &argnum);
		runcommand(arguments, argnum);
		free(command);
		free(arguments);
	}
	return 0;
}
