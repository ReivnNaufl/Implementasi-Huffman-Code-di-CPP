#pragma warning(disable:4996)
#pragma once
#ifndef struct_h
#define struct_h

typedef unsigned char infotype;

typedef struct node {
	int freq;
	infotype info;
	struct node* left, * right;
}node;

typedef struct queue {
	struct queue* next, * prev;
	node* pNode;
}queue;

typedef struct table {
	struct table* next, * prev;
	unsigned char byte;
	char* code;
};

#endif