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
#define TAB 9
#define CTRLR 18
#define CTRLS 19
#define ALTF4 107
#define CTRLF 6
#define YES 1
#define NO 0
int fexist = NO;
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
//seeking a char in the list form the current position to the begining and end for 0 and 1 respectively
int seekchar(nodeptr position, int direction, int value);
void toleft(nodeptr position);
void toright(nodeptr position);
void readfromfile(nodeptr *start, nodeptr position);
void printtofile(nodeptr start);
void openexe(char *, char *);
void findstring(nodeptr start);
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
		case SPACE:
			printf(" ");
			break;
		case TAB:
			printf("\t");
			break;
		case ENTER:
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

	printf("\033[1000D");
	printf("\033[1000A");
	nodeptr cur = start;
	while (cur != position.next)
	{
		switch (cur->data) {
		case TAB:
			printf("\033[8C");
			break;
		case ENTER:
			printf("\033[B");
			printf("\033[1000D");
			break;
		default:
			printf("\033[C");
			break;
		}
		cur = cur->next;
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
void openexe(char *command, char *msg)
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

//read a .txt file and insert it into editor
void readfromfile(nodeptr *start, nodeptr position)
{
	openexe("getfilename.exe", NULL);
	FILE *fptr;
	fptr = fopen("filename.txt", "r");
	if (fptr == NULL) {
		openexe("printmassage.exe", "ERROR(with_getfilename.exe)");
		return;
	}
	char string[50];
	fgets(string, 50, fptr);
	for (int i = strlen(string); i >= 0; i--)
		if (string[i] == '\n')
			string[i] = '\0';
	fclose(fptr);
	fptr = fopen(string, "r");
	if (fptr == NULL) {
		openexe("printmassage.exe", "The_file_doesn't_exist_!!!");
		return;
	}
	*start = NULL;
	position->next = NULL;
	position->previous = NULL;
	int  c;
	while (!feof(fptr))
	{
		c = fgetc(fptr);
		insert(start, position, c);
	}
	fexist = YES;
}
void printtofile(nodeptr start)
{
	char choice;
	if (fexist == YES)
	{
		openexe("printmassage.exe", "You_either_loaded_this_document_from_a_file_or_saved_it_before(..press_enter_to_continue)");
		openexe("getuserchoice.exe", "Do_you_want_to_over_write_the_previous_file?_press_'y'_for_yes_and_'n'_for_no!!!");
		FILE *fptr;
		fptr = fopen("userchoice.txt", "r");
		choice = fgetc(fptr);
		fclose(fptr);
		if (choice == 'n' || choice == 'N')
			openexe("getfilename.exe", NULL);
	}
	else
		openexe("getfilename.exe", NULL);
	FILE *fptr;
	fptr = fopen("filename.txt", "r");
	if (fptr == NULL) {
		openexe("printmassage.exe", "ERROR(with_getfilename.exe)");
		return;
	}
	char string[50];
	fgets(string, 50, fptr);
	for (int i = strlen(string); i >= 0; i--)
		if (string[i] == '\n')
			string[i] = '\0';
	fclose(fptr);
	fptr = fopen(string, "w");
	if (fptr == NULL) {
		openexe("printmassage.exe", "The_file_doesn't_exist_!!!");
		return;
	}
	if (start == NULL) {
		fclose(fptr);
		return;
	}
	nodeptr cur = start;
	//printing the list
	while (cur != NULL)
	{
		switch (cur->data) {
		case SPACE:
			fprintf(fptr, " ");
			break;
		case TAB:
			fprintf(fptr, "\t");
			break;
		case ENTER:
			fprintf(fptr, "\n");
			break;
		default:
			fprintf(fptr, "%c", cur->data);
			break;
		}
		cur = cur->next;
	}
	fclose(fptr);
	openexe("printmassage.exe", "Saved_successfully...");
	fexist = YES;
}
void findstring(nodeptr start)
{
	//counting the nodes
	int numofnodes = 0;
	nodeptr cur = start;

	while (cur != NULL) {
		numofnodes++;
		cur = cur->next;
	}
	//convert the list to a string
	char *string;
	string = (char *)malloc(sizeof(char)*(numofnodes + 1));
	cur = start;
	int i = 0;
	while (cur != NULL) {
		string[i++] = cur->data;
		cur = cur->next;
	}
	string[i] = '\0';
	//getting the phrase from the user
	char phrase[50];
	openexe("getuserchoice.exe", "Enter_the_string_you_want_to_find\n");
	FILE *fptr;
	fptr = fopen("userchoice.txt", "r");

	if (fptr == NULL)
	{
		openexe("printmassage.exe", "ERROR(WITH_USERCHOICE.EXE");
		return;
	}
	fgets(phrase, 50, fptr);
	fclose(fptr);

	for (int i = strlen(phrase) - 1; i >= 0; i--) {
		if (phrase[i] == '\n')
			phrase[i] = '\0';
	}
	char *temp;
	int numfound = 0;
	temp = strstr(string, phrase);
	while (temp != NULL)
	{
		numfound++;
		temp++;
		temp = strstr(temp, phrase);
	}
	if (numfound == 0)
		return;
	int *num;
	num = (int *)malloc(sizeof(int)*numfound);
	temp = strstr(string, phrase);
	for (size_t i = 0; temp != NULL; i++)
	{
		*(num + i) = temp - string;
		temp++;
		temp = strstr(temp, phrase);
	}
	*(num + i) = -1;
	int phraselen = strlen(phrase);
	//printing the list
	cur = start;
	int j = 0;
	system("cls");
	for (i = 0; cur != NULL; i++)
	{
		if (i == *(num + j))
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1760 | 011);
		if (i == (*(num + j))+phraselen)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
			j++;
		}
		switch (cur->data) {
		case SPACE:
			printf(" ");
			break;
		case TAB:
			printf("\t");
			break;
		case ENTER:
			printf("\n");
			break;
		default:
			printf("%c", cur->data);
			break;
		}
		cur = cur->next;
	}
}