#include"functions.h"
int main()
{
	char *command;
	char **arguments;
	while (1) {
		command = getcommand();
		arguments = parscommand(command);
		runcommand(arguments);
	}
	free(command);
	free(arguments);
	return 0;
}
