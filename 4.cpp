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
struct Node {
	int data;
	struct Node *next;
	struct Node *previous;
};


typedef struct Node node;
typedef node * nodeptr;


void insert(nodeptr *start, nodeptr position, int value);
void Delete(nodeptr *start, nodeptr position);
void print(nodeptr start, node position);



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
			system("cls");
			print(start, position);
			break;
		case KEYCONST:
			character = getch();
			switch (character) {
			case LEFT:
				if (position.previous == NULL)
					break;
				position.next = position.previous;
				position.previous = (position.previous)->previous;
				system("cls");
				print(start, position);
			}
			break;
		default:
			insert(&start, &position, character);
			system("cls");
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