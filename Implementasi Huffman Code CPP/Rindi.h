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

// Function untuk membangun Huffman Tree dari queue yang berisi node-node dengan frekuensi tertentu
nAddress buildHuffmanTree(qAddress* head);

// Procedure untuk print value pada node
void printNodeValue(node* n);

// Procedure untuk print Huffman Tree dengan format tertentu
void printTree(node* root, bool isRight, const char* indent);

// Procedure untuk print seluruh Huffman Tree
void printBinaryTree(node* root);

// Procedure untuk menghasilkan kode Huffman untuk setiap karakter dan menyimpannya dalam code table
void generateCodes(nAddress root, char* code, int top, table* codeTable);

// Procedure untuk print semua kode Huffman yang tersimpan dalam code table
void printCodes(tAddress codeTable);

// Procedure untuk deallocate semua node dalam Huffman Tree dari memori
void deallocateTree(nAddress root);

// Procedure untuk deallocate semua entri dalam code table dari memori
void deallocateTable(tAddress codeTable);

//Function untuk menampilkan main menu dan mereturn pilihan
int mainMenu();

#endif