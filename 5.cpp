#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#define BACKSPACE 8
#define KEYCONST 224
#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80
#define DELETE 83
#define ENTER 13
#define SPACE 32
struct Node {
	int data;
	struct Node *next;
	struct Node *previous;
};
typedef struct Node node;
typedef node * nodeptr;
//prototypes
void insert(nodeptr *start, nodeptr position, int value);
void Delete(nodeptr *start, nodeptr position);
void print(nodeptr start, node position);
void setcursor(nodeptr start, node position);
;//seeking a char in the list form the current position to the begining and end for 0 and 1 respectively
int seekchar(nodeptr position, int direction, int value);
void toleft(nodeptr position);
void toright(nodeptr position);
void openexe(char *);
int main()
{
	int character;
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
					break;
			case DELETE:
				if (position.next == NULL)
					break;
				position.previous = position.next;
				position.next = (position.next)->next;
				Delete(&start, &position);
				print(start, position);
			}
			break;
		default:
			insert(&start, &position, character);
			print(start, position);
			break;
		}
	}
	getch();
	return 0;
}
//insert function to insert a char in the linked list
void insert(nodeptr *start, nodeptr position, int value)
{

	//making a new list
	if (*start == NULL)
	{
		nodeptr newptr;
		newptr = (nodeptr)malloc(sizeof(node));
		newptr->data = value;
		*start = newptr;
		newptr->next = NULL;
		newptr->previous = NULL;
		position->next = NULL;
		position->previous = newptr;
		return;
	}
	//insert in the begining of the list
	if (position->previous == NULL) {
		nodeptr newptr;
		newptr = (nodeptr)malloc(sizeof(node));
		newptr->data = value;
		*start = newptr;
		newptr->previous = NULL;
		newptr->next = position->next;
		position->previous = newptr;
		return;
	}

	//insert at the end of the list
	if (position->next == NULL)
	{
		nodeptr newptr;
		newptr = (nodeptr)malloc(sizeof(node));
		newptr->data = value;
		newptr->next = NULL;
		newptr->previous = position->previous;
		(position->previous)->next = newptr;
		position->next = NULL;
		position->previous = newptr;
		return;
	}
	//insert otherwise
	nodeptr newptr;
	newptr = (nodeptr)malloc(sizeof(node));
	newptr->data = value;
	newptr->next = position->next;
	newptr->previous = position->previous;
	(position->previous)->next = newptr;
	(position->next)->previous = newptr;
	position->previous = newptr;


}
//delte a char from the list
void Delete(nodeptr *start, nodeptr position)
{
	//the cursor be in the beginning

	if (position->previous == NULL)
		return;

	//deleting the first node

	if (*start == position->previous)
	{
		free(position->previous);
		position->previous = NULL;
		*start = position->next;
		return;
	}

	//delete the last node
	nodeptr temp;
	if (position->next == NULL)
	{
		temp = (position->previous)->previous;
		free(position->previous);
		position->previous = temp;
		(position->previous)->next = NULL;
		return;
	}

	//delete otherwise
	temp = (position->previous)->previous;
	free(position->previous);
	temp->next = position->next;
	position->previous = temp;
	(position->next)->previous = temp;
}
// print
void print(nodeptr start, node position)
{
	system("cls");
	if (start == NULL)
		return;
	nodeptr cur = start;
	//printing the list
	while (cur != NULL)
	{
		switch (cur->data) {
		case 32:
			printf(" ");
			break;
		case 9:
			printf("\t");
			break;
		case 13:
			printf("\n");
			break;
		default:
			printf("%c", cur->data);
			break;
		}
		cur = cur->next;
	}
	setcursor(start, position);
}

//set the blinking cursor position in the screen
void setcursor(nodeptr start, node position)
{
	if (position.next == NULL)
		return;

	//defining a temporary position elemt
	node tempos;
	tempos.next = NULL;
	tempos.previous = start;

	//finding the last element
	while ((tempos.previous)->next != NULL)
		tempos.previous = (tempos.previous)->next;

	//setting the cursor
	while (position.previous != tempos.previous) {
		printf("\033[D");
		tempos.previous = (tempos.previous)->previous;
	}
}

//seeking a char in the list form the current position to the begining and end for 0 and 1 respectively
//wont change the position if it couldnt find the char 
//the cursor position to the left of the specified character
int seekchar(nodeptr position, int direction, int value)
{
	node temp;
	temp = *position;
	switch (direction)
	{
	case LEFT:
		if (temp.previous == NULL)
			return 0;
		while ((temp.previous)->data != value) {
			toleft(&temp);
			if (temp.previous == NULL)
				return 0;
		}
		toleft(&temp);
		*position = temp;
		return 1;
	case RIGHT:
		if (temp.next == NULL)
			return 0;
		while ((temp.next)->data != value) {
			toright(&temp);
			if (temp.next == NULL)
				return 0;
		}
		*position = temp;
		return 1;
	}

}

void openexe(char *command)
{
	// additional information
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// start the program up
	CreateProcessA
		(
			command,   // the path
			NULL,                // Command line
			NULL,                   // Process handle not inheritable
			NULL,                   // Thread handle not inheritable
			FALSE,                  // Set handle inheritance to FALSE
			CREATE_NEW_CONSOLE,     // Opens file in a separate console
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&si,            // Pointer to STARTUPINFO structure
			&pi           // Pointer to PROCESS_INFORMATION structure
			);
	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
void toleft(nodeptr position)
{
	position->next = position->previous;
	position->previous = (position->previous)->previous;
}
void toright(nodeptr position)
{
	position->previous = position->next;
	position->next = (position->next)->next;
}
