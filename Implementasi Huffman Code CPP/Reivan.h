#pragma once
#ifndef Reivan_h
#define Reivan_h

#include "struct.h"

//Fungsi untuk membuat node baru bertipe node dengan menginisialisasikan value sesuai dengan parameter 
nAddress createNode(infotype infoIns);

//fungsi unruk mengecek apakah byte sudah ada dalam suatu list atau tidak
bool isDupe(qAddress head, infotype check);

//Fungsi untuk membuat node baru bertipe queue dengan menginisialisasikan value sesuai dengan parameter 
qAddress createQueueNode(nAddress nodePtr);

//Procedure untuk untuk memasukan node baru kedalam akhir queue
void queueInsert(qAddress* head, qAddress newNode);

//procedure untuk menambahkan freq node dengan info container 
void freqPlusOne(qAddress head, infotype container);

//Function untuk membuat queue berisi byte byte unik suatu file dan menghitung freq amsing masing byte
qAddress createList(char* fileName);

//Procedure untuk menampilkan queue ke layar
void printList(qAddress head);

//Procedure untuk mengesort ascending queue berdasarkan freq dan byte
void mergeSort(qAddress* head);

//Procedure untuk memecah queue menjadi 2
void splitList(qAddress src, qAddress* lList, qAddress* rList);

//Function untuk manggabungkan 2 queue secara sorted ascending berdasarkan freq dan byte
qAddress merge(qAddress lSubList, qAddress rSubList);

//Function untuk menampilkan main menu dan mereturn pilihan
int mainMenu();

//Print eks
char* fprintHeader(char* filename, nAddress head);

void countNodes(nAddress head, int* count);

void fprintPreOrder(nAddress head, FILE* filename);

nAddress constructTree(char* filename);

nAddress readTree(FILE* file);

#endif