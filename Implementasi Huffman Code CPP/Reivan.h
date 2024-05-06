#pragma once
#ifndef Reivan_h
#define Reivan_h

#include <stdio.h>
#include <stdlib.h>

#define byte unsigned char
#define red(X) (X)->info.red
#define blue(X) (X)->info.blue
#define green(X) (X)->info.green
#define freq(X) (X)->freq
#define left(X) (X)->left
#define right(X) (X)->right
#define next(X) (X)->next
#define prev(X) (X)->prev

typedef struct{
	byte red, green, blue;
}infotype;

typedef struct node{
	int freq;
	infotype info;
	struct node *left, *right;
}node;

typedef struct queue{
	struct queue *next, *prev;
	node *node;
}queue;


#endif