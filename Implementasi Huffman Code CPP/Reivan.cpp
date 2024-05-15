#include <stdio.h>
#include <stdlib.h>
#include "Reivan.h"

nAddress createNode(infotype infoIns) {
	nAddress nodePtr = (nAddress)malloc(sizeof(node));

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

qAddress createQueueNode(nAddress nodePtr) {
	qAddress qPtr = (qAddress)malloc(sizeof(queue));

	if (qPtr != NULL) {
		pNode(qPtr) = nodePtr;
		next(qPtr) = NULL;
		return qPtr;
	}
	else {
		printf("ALOKASI MEMORI GAGAL!");
		exit(1);
	}
}

bool isDupe(qAddress head, infotype check) {
	qAddress p = head;

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

void queueInsert(qAddress* head, qAddress newNode) {
	qAddress p = *head;

	if (*head == NULL) {
		*head = newNode;
	}
	else {
		while (next(p) != NULL) {
			p = next(p);
		}
		next(p) = newNode;
	}
}

void freqPlusOne(qAddress head, infotype container) {
	qAddress p = head;

	while (info(pNode(p)) != container) {
		p = next(p);
	}
	freq(pNode(p)) += 1;
}

qAddress createList(char *fileName) {
	FILE* fFile;
	nAddress nodePtr;
	qAddress qPtr = NULL, head = NULL;
	infotype byteContainer;

	fFile = fopen(fileName, "rb");
	if (fFile == NULL) {
		printf("GAGAL MEMUAT FILE!");
		exit(1);
	}
	byteContainer = fgetc(fFile);
	
	while (!feof(fFile)) {
		if (isDupe(head, byteContainer)) {
			freqPlusOne(head, byteContainer);
		}
		else {
			nodePtr = createNode(byteContainer);
			qPtr = createQueueNode(nodePtr);
			queueInsert(&head, qPtr);
		}
		byteContainer = fgetc(fFile);
	}

	return head;
}

void printList(qAddress head) {
	qAddress p = head;
	int total = 0;

	while (p != NULL) {
		printf("%x %d\n", info(pNode(p)), freq(pNode(p)));
		total += freq(pNode(p));
		p = next(p);
	}
	printf("\n%d", total);
}