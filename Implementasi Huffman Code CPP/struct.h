#pragma warning(disable:4996)
#pragma once
#ifndef struct_h
#define struct_h

#define info(X) (X)->info
#define freq(X) (X)->freq
#define left(X) (X)->left
#define right(X) (X)->right
#define next(X) (X)->next
#define prev(X) (X)->prev
#define pNode(X) (X)->pNode
#define byte(X) (X)->byte
#define code(X) (X)->code

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
	infotype byte;
	char* code;
};

#endif