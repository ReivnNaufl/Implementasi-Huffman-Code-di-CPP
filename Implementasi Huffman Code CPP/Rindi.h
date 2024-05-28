/*	
Program		: Rindi.h
Deskripsi	: Header untuk build dan print HuffmanTree, 
              generate dan print Code, dealokasi Tree dan Table
Dibuat oleh : Rindi Indriani (231511030) 
Kelompok	: 2
Kelas		: 1A
Jurusan     : Teknik Komputer dan Informatika
Prodi       : D3 Teknik Informatika
Angkatan    : 2023/2024
Tanggal		: 23/05/2024
===============================================*/

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
void deallocateTree(nAddress root);
void deallocateTable(tAddress codeTable);
//Function untuk menampilkan main menu dan mereturn pilihan
int mainMenu();

#endif