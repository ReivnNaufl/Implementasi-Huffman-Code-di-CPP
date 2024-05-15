#pragma once
#ifndef Reivan_h
#define Reivan_h

#include "struct.h"

nAddress createNode(infotype infoIns);

bool isDupe(qAddress head, infotype check);

qAddress createQueueNode(nAddress nodePtr);

void queueInsert(qAddress* head, qAddress newNode);

void freqPlusOne(qAddress head, infotype container);

qAddress createList(char* fileName);

void printList(qAddress head);

#endif