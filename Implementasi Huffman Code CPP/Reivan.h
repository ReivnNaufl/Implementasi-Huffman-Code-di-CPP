/*
Program		: Reivan.cpp
Deskripsi	: Header untuk membaca file dan membuat list byte dan frequensinya, sorting list ascending menggunakan merge sort,
			  mencetak bagian header encoded file, membaca dan membuat tree dari file, dan function compare size file.
Dibuat oleh : Muhammad Reivan Naufal Mufid (231511021)
Kelompok	: 2
Kelas		: 1A
Jurusan     : Teknik Komputer dan Informatika
Prodi       : D3 Teknik Informatika
Angkatan    : 2023/2024
Tanggal		: 14 Mei 2024
===============================================*/

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

//Print ekstensi file, panjang byte tree, dan tree ke awal file encoded
char* fprintHeader(char* filename, nAddress head);

//Procedure untuk menghitung node tree
void countNodes(nAddress head, int* count);

//Print tree ke file dengan preorder traversal
void fprintPreOrder(nAddress head, FILE* filename);

//Function untuk membuat tree dari header file
nAddress constructTree(char* filename);

//Function pembantu construct tree
nAddress readTree(FILE* file);

//Procedure untuk membandingkan besar dari 2 file
void compare(char* fileA, char* fileB);

#endif