#include <stdio.h>
#include <stdlib.h>
#include "Reivan.h"

node* createNode(infotype infoIns) {
	node* nodePtr = (node*)malloc(sizeof(node));

	if (nodePtr != NULL) {
		freq(nodePtr) = 0;
		info(nodePtr) = infoIns;
		left(nodePtr) = NULL;
		right(nodePtr) = NULL;
		return nodePtr;
	}
	else {
		printf("ALOKASI MEMORI GAGAL!");
		exit(1);
	}
}

bool isDupe(queue* head, infotype check) {
	queue* p = head;

	while (p != NULL) {
		if (info(pNode(p)) == check) {
			return true;
		}
		else {
			p = next(p);
		}
	}
	return false;
}
/*
queue* createList(char *fileName) {
	FILE* fFile;
	queue* qPtr = NULL;

	fFile = fopen(fileName, "rb");
	if (fFile == NULL) {
		printf("GAGAL MEMUAT FILE!");
		exit(1);
	}

	while (!feof(fFile)) {

	}
}*/