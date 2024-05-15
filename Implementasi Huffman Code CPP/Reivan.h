#pragma once
#ifndef Reivan_h
#define Reivan_h

#include "struct.h"

node* createNode(infotype infoIns);

bool isDupe(queue* head, infotype check);

queue* createQueueNode(node* nodePtr);

void queueInsert(queue* head, queue* newNode);

void freqPlusOne(queue* head, infotype container);

void printList(queue* head);

#endif