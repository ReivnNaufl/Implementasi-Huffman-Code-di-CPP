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
	printf("\n%d\n-----\n\n", total);
}

void mergeSort(qAddress *head) {
	qAddress pHead = *head, left, right;

	if ((pHead == NULL) || (next(pHead) == NULL)) {
		return;
	}

	splitList(pHead, &left, &right);

	mergeSort(&left);
	mergeSort(&right);

	*head = merge(left, right);
}

void splitList(qAddress src, qAddress* lSubList, qAddress* rSubList) {
	qAddress mid = src, end = next(src);

	while (end != NULL) {
		end = next(end);
		if (end != NULL) {
			end = next(end);
			mid = next(mid);
		}
	}

	*lSubList = src;
	*rSubList = next(mid);
	next(mid) = NULL;
}

qAddress merge(qAddress lSubList, qAddress rSubList) {
	qAddress merged = NULL, lPtr = lSubList, rPtr = rSubList, temp = NULL;

	while ((lPtr != NULL) and (rPtr != NULL)) {
		if (freq(pNode(lPtr)) < freq(pNode(rPtr))) {
			queueInsert(&merged, lPtr);
			temp = lPtr;
			lPtr = next(lPtr);
			next(temp) = NULL;
		}
		else if (freq(pNode(lPtr)) > freq(pNode(rPtr))) {
			queueInsert(&merged, rPtr);
			temp = rPtr;
			rPtr = next(rPtr);
			next(temp) = NULL;
		}
		else {
			if (info(pNode(lPtr)) < info(pNode(rPtr))) {
				queueInsert(&merged, lPtr);
				temp = lPtr;
				lPtr = next(lPtr);
				next(temp) = NULL;
			}
			else {
				queueInsert(&merged, rPtr);
				temp = rPtr;
				rPtr = next(rPtr);
				next(temp) = NULL;
			}
		}
	}

	if (lPtr == NULL) {
		queueInsert(&merged, rPtr);
	}

	if (rPtr == NULL) {
		queueInsert(&merged, lPtr);
	}

	return merged;
}