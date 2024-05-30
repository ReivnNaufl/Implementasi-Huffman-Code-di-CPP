/*	
Program		: Rindi.cpp
Deskripsi	: Body prototype untuk build dan print HuffmanTree, 
              generate dan print Code, dealokasi Tree dan Table
Dibuat oleh : Rindi Indriani (231511030) 
Kelompok	: 2
Kelas		: 1A
Jurusan     : Teknik Komputer dan Informatika
Prodi       : D3 Teknik Informatika
Angkatan    : 2023/2024
Tanggal		: 23/05/2024
===============================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "Reivan.h"
#include "Rindi.h"
#include <conio.h>
#include <winnt.h>
#include <winbase.h>
#include <wincon.h>
#define panjang 6000

#define BLACK           0
#define DARK_BLUE       1
#define GREEN           2
#define TURQUOISE       3
#define DARK_RED        4
#define PURPLE          5
#define FOREST_GREEN    6
#define LIGHT_GRAY      7
#define GRAY            8
#define BLUE            9
#define LIGHT_GREEN    10
#define LIGHT_BLUE     11
#define RED            12
#define PINK           13
#define YELLOW         14
#define WHITE          15
#define STDALERT      140
#define STDHEADER     143
#define STDBACKGROUND 159

// Function untuk membangun Huffman Tree dari queue yang berisi node-node dengan frekuensi tertentu
nAddress buildHuffmanTree(qAddress* head) {
    while (next(*head) != NULL) {
        // Mengambil dua node dengan frekuensi terkecil dari queue
        nAddress left = pNode(*head);
        qAddress temp = *head;
        *head = next(*head);
        free(temp);

        nAddress right = pNode(*head);
        temp = *head;
        *head = next(*head);
        free(temp);

        // Membuat node internal baru dengan kedua node sebagai anak-anaknya
        nAddress newNode = createNode(0);  // Informasi pada node internal tidak penting
        freq(newNode) = freq(left) + freq(right);
        left(newNode) = left;
        right(newNode) = right;

        // Insert node baru kembali ke dalam queue
        qAddress newQueueNode = createQueueNode(newNode);
        queueInsert(head, newQueueNode);

        // Sort the queue again
        mergeSort(head);
    }

    // Node yang tersisa adalah root dari Huffman Tree
    return pNode(*head);
}

// Procedure untuk print value pada node
void printNodeValue(node* n) {
    if (n == NULL) {
        printf("<null>");
    }
    else {
        printf("%d", (int)info(n));  // Assuming info is the value you want to print
    }
    printf("\n");
}


// Procedure untuk print Huffman Tree dengan format tertentu
void printTree(node* root, bool isRight, const char* indent) {
    if (right(root) != NULL) {
        char* newIndent = (char*)malloc(strlen(indent) + 10);
        sprintf(newIndent, "%s%s", indent, (isRight ? "        " : " |      "));
        printTree(right(root), true, newIndent);
        free(newIndent);
    }

    printf("%s", indent);
    if (isRight) {
        printf(" /----- ");
    }
    else {
        printf(" \\----- ");
    }
    printNodeValue(root);

    if (left(root) != NULL) {
        char* newIndent = (char*)malloc(strlen(indent) + 10);
        sprintf(newIndent, "%s%s", indent, (isRight ? " |      " : "        "));
        printTree(left(root), false, newIndent);
        free(newIndent);
    }
}

// Procedure untuk print seluruh Huffman Tree
void printBinaryTree(node* root) {
    if (root != NULL) {
        printTree(root, false, "");
    }
}

// Procedure untuk menghasilkan kode Huffman untuk setiap karakter dan menyimpannya dalam code table
void generateCodes(nAddress root, char* code, int top, table* codeTable) {
    if (left(root)) {
        code[top] = '0';
        generateCodes(left(root), code, top + 1, codeTable);
    }

    if (right(root)) {
        code[top] = '1';
        generateCodes(right(root), code, top + 1, codeTable);
    }

    if (!left(root) && !right(root)) {
        code[top] = '\0';
        tAddress newTableEntry = (tAddress)malloc(sizeof(table));
        byte(newTableEntry) = info(root);
        code(newTableEntry) = (char*)malloc(top + 1);
        strcpy(code(newTableEntry), code);
        next(newTableEntry) = codeTable->next;
        codeTable->next = newTableEntry;
    }
}

// Procedure untuk print semua kode Huffman yang tersimpan dalam code table
void printCodes(tAddress codeTable) {
    tAddress p = codeTable;
    while (p != NULL) {
        printf("Byte: %x, Code: %s\n", byte(p), code(p));
        p = next(p);
    }
}

// Procedure untuk deallocate semua node dalam Huffman Tree dari memori
void deallocateTree(nAddress root) {
    if (root == NULL) {
        return;
    }

    // Deallocate left subtree
    deallocateTree(left(root));

    // Deallocate right subtree
    deallocateTree(right(root));

    // Deallocate the current node
    free(root);
}

// Procedure untuk deallocate semua entri dalam code table dari memori
void deallocateTable(tAddress codeTable) {
    tAddress current = codeTable;
    while (current != NULL) {
        tAddress next = next(current);
        free(code(current));  // Deallocate the code string
        free(current);        // Deallocate the table entry
        current = next;
    }
}

void warnateks(int warna) { 
    HANDLE hConsole; 
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, warna);
}

// void gotoxy(int x, int y) { 
//     HANDLE hConsoleOutput;  
//     COORD dwCursorPosition;  
//     dwCursorPosition.X = x;  
//     dwCursorPosition.Y = y;  
//     hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);  
//     SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);   
// }

//Function untuk menampilkan main menu dan mereturn pilihan
int mainMenu() {
	int cursor = 1, input;

	  for (;;) {
        system("cls");
        warnateks(PURPLE);
        printf("                                   __ __     ______                  _____        __                                \n");
        printf("                                  / // /_ __/ _/ _/_ _  ___ ____    / ___/__  ___/ /__                              \n");
        printf("                                 / _  / // / _/ _/  ' \\/ _ `/ _ \\  / /__/ _ \\/ _  / -_)                          \n");
        printf("                                /_//_/\\_,_/_//_//_/_/_/\\_,_/_//_/  \\___/\\___/\\_,_/\\__/                        \n");
        printf("                                                                                                                    \n");
        warnateks(YELLOW);
        printf("                                    ==========================================                                      \n");
        printf("                                                      MENU                                                          \n");
        printf("                                    ==========================================                                      \n");
        
        warnateks(cursor == 1 ? PURPLE : WHITE);
        printf("                                        %c Encode\n", (cursor == 1) ? '>' : ' ');
        warnateks(cursor == 2 ? PURPLE : WHITE);
        printf("                                        %c Decode\n", (cursor == 2) ? '>' : ' ');
        warnateks(cursor == 3 ? PURPLE : WHITE);
        printf("                                        %c Help\n", (cursor == 3) ? '>' : ' ');
        warnateks(cursor == 4 ? PURPLE : WHITE);
        printf("                                        %c Quit\n", (cursor == 4) ? '>' : ' ');

        input = getch();

		switch (input)
		{
		case 72: // up arrow key
                cursor = (cursor <= 1) ? 4 : cursor - 1;
                break;
            case 80: // down arrow key
                cursor = (cursor >= 4) ? 1 : cursor + 1;
                break;
            case 13: // enter key
                return cursor;
                break;
            default:
                break;
		}
	}
}