#include <stdio.h>
#include <stdlib.h>
#include "Reivan.h"

node* createNode(infotype infoIns) {
	node* nodePtr = (node*)malloc(sizeof(node));

	if (nodePtr != NULL) {
		freq(nodePtr) = 1;
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

queue* createQueueNode(node* nodePtr) {
	queue* qPtr = (queue*)malloc(sizeof(queue));

	if (qPtr != NULL) {
		pNode(qPtr) = nodePtr;
		next(qPtr) = NULL;
		prev(qPtr) = NULL;
		return qPtr;
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

void queueInsert(queue* head, queue* newNode) {
	queue* p = head;

	if (head == NULL) {
		head = newNode;
	}
	else {
		while (next(p) != NULL) {
			p = next(p);
		}
		next(p) = newNode;
	}
}

void freqPlusOne(queue* head, infotype container) {
	queue* p = head;

	while (info(pNode(p)) != container) {
		p = next(p);
	}
	freq(pNode(p)) += 1;
}

queue* createList(char *fileName) {
	FILE* fFile;
	node* nodePtr;
	queue* qPtr = NULL, *head = NULL;
	infotype byteContainer;

	fFile = fopen(fileName, "rb");
	if (fFile == NULL) {
		printf("GAGAL MEMUAT FILE!");
		exit(1);
	}

	while (!feof(fFile)) {
		byteContainer = fgetc(fFile);
		if (isDupe(head, byteContainer)) {
			freqPlusOne(head, byteContainer);
		}
		else {
			nodePtr = createNode(byteContainer);
			qPtr = createQueueNode(nodePtr);
			queueInsert(head, qPtr);
		}
	}

	return head;
}