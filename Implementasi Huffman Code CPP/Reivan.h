#pragma once
#ifndef Reivan_h
#define Reivan_h

#include "struct.h"

#define info(X) (X)->info
#define freq(X) (X)->freq
#define left(X) (X)->left
#define right(X) (X)->right
#define next(X) (X)->next
#define prev(X) (X)->prev
#define pNode(X) (X)->pNode

node* createNode(infotype infoIns);

bool isDupe(queue* head, infotype check);

#endif