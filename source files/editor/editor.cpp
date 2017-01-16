#include"editor-variables.h"
#include"editor-functions.h"
int myeditor(char **arguments)
{
	int character;
	int prevchoice = -1;
	node position;
	position.next = position.previous = NULL;

	nodeptr start;
	start = NULL;

	nodeptr buffstart;
	buffstart = NULL;
	node buffpos;
	buffpos.next = buffpos.previous = NULL;
	clearscreen();
	if (arguments[1] != NULL) {
		readfromfile(&start, &position, arguments[1]);
		print(start, position);
	}
	while (1) {

		character = getch();
		
		switch (character)
		{
		case BACKSPACE:
			Delete(&start, &position);
			print(start, position);
			break;
		case CTRLR:
			readfromfile(&start, &position,getfilename());
			print(start, position);
			break;
		case CTRLS:
			printtofile(start);
			break;
		case CTRLF:
			findstring(start);
			break;
		case CTRLC:
			copy(start, &buffstart, &buffpos, prevchoice);
			break;
		case CTRLV:
			paste(&start, &position, buffstart);
			print(start, position);
			break;
		case 0:
		case KEYCONST:
			character = getch();
			switch (character) {
			case LEFT:
				if (position.previous == NULL)
					break;
				toleft(&position);
				print(start, position);
				break;
			case RIGHT:
				if (position.next == NULL)
					break;
				toright(&position);
				print(start, position);
				break;
			case UP:
				goup(&position);
				print(start, position);
				break;
			case DOWN:
				godown(&position);
				print(start, position);
				break;
			case DELETE:
				if (position.next == NULL)
					break;
				toright(&position);
				Delete(&start, &position);
				print(start, position);
				break;
			case ALTF4:
			{
				char choice;
				openexe("getuserchoice.exe", "Do_you_want_to_exit_?_press_'y'_for_yes_and_'n'_for_no!!!");
				FILE *fptr;
				fptr = fopen("userchoice.txt", "r");
				choice = fgetc(fptr);
				fclose(fptr);
				if (choice == 'n' || choice == 'N')
					break;
				if (prevchoice == CTRLS)
				{
					openexe("printmassage.exe", "going_to_exit");
					return 0;
				}
				else
				{
					printtofile(start);
					openexe("printmassage.exe", "going_to_exit");
					return 0;
				}
			}
			break;
			case CTRLRIGHT:
				select(start, &position, prevchoice, CTRLRIGHT);
				break;
			case CTRLLEFT:
				select(start, &position, prevchoice, CTRLLEFT);
				break;
			case CTRLUP:
				select(start, &position, prevchoice, CTRLUP);
				break;
			case CTRLDOWN:
				select(start, &position, prevchoice, CTRLDOWN);
				break;
			}
			break;
		default:
			insert(&start, &position, character);
			print(start, position);
			break;
		}
		prevchoice = character;
	}
	return 0;
}