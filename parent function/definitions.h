#pragma once
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
#define CTRLRIGHT 116
#define CTRLLEFT 115
#define CTRLUP 141
#define CTRLDOWN 145
#define YES 1
#define NO 0
static int fexist = NO;
struct Node {
	int data;
	struct Node *next;
	struct Node *previous;
};
typedef struct Node node;
typedef node * nodeptr;
static node bselect = { 0 };
static node eselect = { 0 };