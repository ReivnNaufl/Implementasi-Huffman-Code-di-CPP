#pragma once
#ifndef Rindi_h
#define Rindi_h

#include "struct.h"

// Function declarations for Huffman Tree creation and code generation
nAddress buildHuffmanTree(qAddress* head);
void printNodeValue(node* n);
void printTree(node* root, bool isRight, const char* indent);
void printBinaryTree(node* root);
//void printBinaryTree(node* root, int space, int height);
void generateCodes(nAddress root, char* code, int top, table* codeTable);
void printCodes(tAddress codeTable);

#endif