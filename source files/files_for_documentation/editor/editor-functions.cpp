#include"editor-variables.h"
#include"editor-functions.h"
 int fexist = NO;
 node bselect ;
 node eselect ;
void clearscreen()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_BLUE);

	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };    // home for the cursor 
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	// Get the number of character cells in the current buffer. 

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.

	if (!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten))
		return;

	// Get the current text attribute.

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;

	// Set the buffer's attributes accordingly.

	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten))
		return;

	// Put the cursor at its home coordinates.

	SetConsoleCursorPosition(hConsole, coordScreen);

	}
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
	clearscreen();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_GREEN|FOREGROUND_INTENSITY| BACKGROUND_GREEN | BACKGROUND_BLUE );
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

	int x = 0;
	int y = 0;
	nodeptr cur = start;
	while (cur != position.next)
	{
		switch (cur->data) {
		case TAB:
		
			x += 8;
			break;
		case ENTER:
			
			x = 0;
			y += 1;
			break;
		default:
			
			x += 1;
			break;
		}
		cur = cur->next;
	}
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//seeking a char in the list form the current position to the begining and end for 0 and 1 respectively
//wont change the position if it couldnt find the char 
//place the cursor position to the left of the specified character
int seekchar(nodeptr position, int direction, int value, int enable,int *length)
{
	node temp;
	temp = *position;
	int i;
	switch (direction)
	{
	case LEFT:
		if (temp.previous == NULL) {
			*length = 0;
			return 0;
		}
		for (i = 0; (temp.previous)->data != value; i++) {
			toleft(&temp);
			if (temp.previous == NULL)
			{
				*length = i+1;
				return 0;
			}
		}
		toleft(&temp);
		if (enable == YES)
			*position = temp;
		*length = i;
		return 1;
	case RIGHT:
		if (temp.next == NULL) {
			*length = 0;
			return 0;
		}
		for (i = 0; (temp.next)->data != value; i++) {
			toright(&temp);
			if (temp.next == NULL) {
				*length = i+1;
					return 0;
			}
		}
		if (enable == YES)
			*position = temp;
		*length = i;
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
void goup(nodeptr position)
{
	int length1,length2;
	if (seekchar(position, LEFT, ENTER, YES, &length1) == 0)
		return;
	seekchar(position, LEFT, ENTER, NO, &length2);
	if (length2 > length1)
		for (int i = 0; i < length2 - length1; i++)
			toleft(position);
}
void godown(nodeptr position)
{
	int length1,length2;
	seekchar(position, LEFT, ENTER, NO, &length1);
	for (int i = 0; i < 2; i++)
		if (seekchar(position, RIGHT, ENTER, YES,&length2)) {
			if (!i) toright(position);
		}
		else
		{
			while (position->next != NULL)
				toright(position);
		}
	if (length2 > length1)
		for (int i = 0; i < length2 - length1; i++)
			toleft(position);
}
//read a .txt file and insert it into editor
void readfromfile(nodeptr *start, nodeptr position,char *filename)
{
	FILE *fptr;
	fptr = fopen("filename.txt", "w");
	fprintf(fptr, "%s", filename);
	fclose(fptr);
	fptr = fopen(filename, "r");
	if (fptr == NULL) {
		fptr = fopen(filename, "w");
	}
	*start = NULL;
	position->next = NULL;
	position->previous = NULL;
	int  c;
	c = fgetc(fptr);
	while (c!=EOF)
	{
		insert(start, position, c);
		c = fgetc(fptr);
	}
	fclose(fptr);
	fexist = YES;
}
char *getfilename() {
	openexe("getfilename.exe", NULL);
	FILE *fptr;
	fptr = fopen("filename.txt", "r");
	if (fptr == NULL) {
		openexe("printmassage.exe", "ERROR(with_getfilename.exe)");
		return NULL;
	}
	char string[50];
	fgets(string, 50, fptr);
	for (int i = strlen(string); i >= 0; i--)
		if (string[i] == '\n')
			string[i] = '\0';
	fclose(fptr);
	return string;
}
void printtofile(nodeptr start)
{
	char choice;
	if (fexist == NO)
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
	int l;
	for (l = 0; temp != NULL; l++)
	{
		*(num + l) = temp - string;
		temp++;
		temp = strstr(temp, phrase);
	}
	*(num + l) = -1;
	int phraselen = strlen(phrase);
	//printing the list
	cur = start;
	int j = 0;

	clearscreen();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE);

	for (i = 0; cur != NULL; i++)
	{

		if (i == *(num + j)) 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
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
		if (i == (*(num + j)) + phraselen - 1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE);
			j++;
		}
	}
}
void select(nodeptr start, nodeptr position, int prevchoice, int choice)
{
	if (prevchoice != CTRLRIGHT&&prevchoice != CTRLLEFT&&prevchoice != CTRLUP&&prevchoice != CTRLDOWN)
		bselect = *position;
	switch (choice)
	{
	case CTRLRIGHT:
		if (position->next == NULL)
			break;
		toright(position);
		break;
	case CTRLLEFT:
		if (position->previous == NULL)
			break;
		toleft(position);
		break;
	case CTRLUP:
		goup(position);
		break;
	case CTRLDOWN:
		godown(position);
		break;
	}
	eselect = *position;
	clearscreen();
	nodeptr cur = start;
	int flag = 0;
	while (cur != NULL)
	{
		if (flag == 0 && (cur == bselect.next || cur == eselect.next))
			flag = 1;
		else if (flag == 1 && (cur == bselect.next || cur == eselect.next))
			flag = 0;
		if (flag)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN  | BACKGROUND_GREEN | BACKGROUND_BLUE|BACKGROUND_INTENSITY);
		else
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE);
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
		};
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
		cur = cur->next;
	}
	setcursor(start, *position);
}
void emptybuff(nodeptr *buffstart)
{
	if (*buffstart == NULL)
		return;
	nodeptr temp;

	temp = *buffstart;
	while (temp != NULL)
	{
		nodeptr temp2;
		temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
	*buffstart = NULL;
	return;
}
void copy(nodeptr start, nodeptr *buffstart, nodeptr buffpos, int prevchoice)
{
	emptybuff(buffstart);
	if (prevchoice != CTRLRIGHT&&prevchoice != CTRLLEFT&&prevchoice != CTRLUP&&prevchoice != CTRLDOWN)
		return;
	nodeptr cur = start;
	int flag = 0;
	while (cur != NULL)
	{
		if (flag == 0 && (cur == bselect.next || cur == eselect.next))
			flag = 1;
		else if (flag == 1 && (cur == bselect.next || cur == eselect.next))
			flag = 0;
		if (flag)
			insert(buffstart, buffpos, cur->data);
		cur = cur->next;
	}
}
void paste(nodeptr *start, nodeptr position, nodeptr buffstart)
{
	if (buffstart == NULL)
		return;
	nodeptr cur = buffstart;
	while (cur != NULL)
	{
		insert(start, position, cur->data);
		cur = cur->next;
	}
}