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

//Function untuk menampilkan main menu dan mereturn pilihan
int mainMenu() {
	int cursor = 1, input;

	  for (;;) {
        system("cls");
        printf(" __    __             ______    ______                                            ______                   __           \n");
        printf("|  \\  |  \\           /      \\  /      \\                                          /      \\                 |  \\          \n");
        printf("| $$  | $$ __    __ |  $$$$$$\\|  $$$$$$\\ ______ ____    ______   _______        |  $$$$$$\\  ______    ____| $$  ______  \n");
        printf("| $$__| $$|  \\  |  \\| $$_  \\$$| $$_  \\$$|      \\    \\  |      \\ |       \\       | $$   \\$$ /      \\  /      $$ /      \\ \n");
        printf("| $$    $$| $$  | $$| $$ \\    | $$ \\    | $$$$$$\\$$$$\\  \\$$$$$$\\| $$$$$$$\\      | $$      |  $$$$$$\\|  $$$$$$$|  $$$$$$\\\n");
        printf("| $$$$$$$$| $$  | $$| $$$$    | $$$$    | $$ | $$ | $$ /      $$| $$  | $$      | $$   __ | $$  | $$| $$  | $$| $$    $$\n");
        printf("| $$  | $$| $$__/ $$| $$      | $$      | $$ | $$ | $$|  $$$$$$$| $$  | $$      | $$__/  \\| $$__/ $$| $$__| $$| $$$$$$$$\n");
        printf("| $$  | $$ \\$$    $$| $$      | $$      | $$ | $$ | $$ \\$$    $$| $$  | $$       \\$$    $$ \\$$    $$ \\$$    $$ \\$$     \\\n");
        printf(" \\$$   \\$$  \\$$$$$$  \\$$       \\$$       \\$$  \\$$  \\$$  \\$$$$$$$ \\$$   \\$$        \\$$$$$$   \\$$$$$$   \\$$$$$$$  \\$$$$$$$\n");
        printf("                                                                                                                        \n");
        printf("                                                                                                                        \n");
        printf("                                        ==========================================                                      \n");
        printf("                                                          MENU                                                          \n");
        printf("                                        ==========================================                                      \n");
        printf("                                        %c Encode\n", (cursor == 1) ? '>' : ' ');
        printf("                                        %c Decode\n", (cursor == 2) ? '>' : ' ');
        printf("                                        %c Help\n", (cursor == 3) ? '>' : ' ');
        printf("                                        %c Quit\n", (cursor == 4) ? '>' : ' ');

		input = getch();

		switch (input)
		{
		case 72://up arrow key
			if (cursor <= 1) {
				cursor = 4;
			}
			else {
				cursor--;
			}
			break;
		case 80://down arrow key
			if (cursor >= 4) {
				cursor = 1;
			}
			else {
				cursor++;
			}
			break;
		case 13://enter key
			return cursor;
			break;
		default:
			break;
		}
	}
}