#include"functions.h"
int main()
{
	int character;
	int prevchoice = -1;
	node position;
	position.next = position.previous = NULL;

	nodeptr start;
	start = NULL;


	while (1) {

		character = getch();

		switch (character)
		{
		case BACKSPACE:
			Delete(&start, &position);
			print(start, position);
			break;
		case CTRLR:
			readfromfile(&start, &position);
			print(start, position);
			break;
		case CTRLS:
			printtofile(start);
		case CTRLF:
			findstring(start);
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
				seekchar(&position, LEFT, ENTER);
				print(start, position);
				break;
			case DOWN:
				for (int i = 0; i < 2; i++)
					if (seekchar(&position, RIGHT, ENTER)) {
						if (!i) toright(&position);
					}
					else
					{
						while (position.next != NULL)
							toright(&position);
					}
				print(start, position);
				break;
			case DELETE:
				if (position.next == NULL)
					break;
				toright(&position);
				Delete(&start, &position);
				print(start, position);

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