#include <stdio.h>
#include <ctype.h>
#include "Reivan.h"
#include "Rindi.h"
#include "Yazid.h"
#include <Windows.h>
#include <stdlib.h>
#include <stdint.h>
#include <conio.h>



int main() {
    char fileName[256], filePath[256], code[100], *encodedPath;
    int choice = 0;
    qAddress head = NULL;
    nAddress root = NULL;
    table codeTable;
    codeTable.next = NULL;

    for (;;) {
        system("cls");
        choice = mainMenu();
        switch (choice) 
        {
            case 1:
                system("cls");
                printf("Masukan nama file (dengan ekstensi) yang akan di encode: ");
                scanf(" %s", fileName);
                sprintf(filePath, "INPUT/Untuk-di-encode/%s", fileName);
                system("cls");

                head = createList(filePath);
                mergeSort(&head);

                root = buildHuffmanTree(&head);
                printf("Huffman Tree:\n");
                printBinaryTree(root);

                generateCodes(root, code, 0, &codeTable);
                printf("Huffman Codes:\n");
                printCodes(codeTable.next);

                encodedPath = fprintHeader(fileName, root);

                encode(filePath, codeTable, encodedPath);

                compare(filePath, encodedPath);

                printf("Tekan tombol apapun untuk melanjutkan ");
                getch();

                system("cls");

                //dealloc table and tree here
                root = NULL;
                codeTable.next = NULL;

                break;
            case 2:
                system("cls");
                printf("Masukan nama file (dengan ekstensi) yang akan di decode: ");
                scanf(" %s", fileName);
                sprintf(filePath, "INPUT/Untuk-di-decode/%s", fileName);
                system("cls");

                decode(filePath);

                printf("Decode selesai!\n\n");
                printf("Tekan tombol apapun untuk melanjutkan ");
                getch();

                break;
            case 3:
                return 0;
            case 4:
                break;
        }
    }
}

/*
int main() {
    // Step 1: Create a list from the input file
    qAddress head = createList((char*)"INPUT/Untuk-di-encode/classic.bmp");
    printf("Initial list:\n");
    printList(head);

    // Step 2: Sort the list by frequency
    mergeSort(&head);
    printf("Sorted list:\n");
    printList(head);

    // Step 3: Build the Huffman Tree
    nAddress root = buildHuffmanTree(&head);

    // Step 4: Print the Huffman Tree
    printf("Huffman Tree:\n");
    printBinaryTree(root);
    //  printBinaryTree(root, 0, 10);
   
        // Step 5: Generate Huffman Codes
    table codeTable;
    codeTable.next = NULL;

    char code[100];  // A buffer to hold the current code
    generateCodes(root, code, 0, &codeTable);

    // Step 6: Print the Huffman Codes
    printf("Huffman Codes:\n");
    printCodes(codeTable.next);

    char* hasil = fprintHeader((char*)"classic.bmp", root);

    encode((char*)"INPUT/Untuk-di-encode/classic.bmp", codeTable,hasil);

    FILE* tree = fopen("tree.txt", "wb");

    fprintPreOrder(root,tree);

    unsigned char buffer[4];

    baca4byte(hasil, buffer);
    
    uint32_t num = asciiToInt(buffer);

    printf("%d", num );

    nAddress root1 = constructTree(hasil);
    printf("\n\n");
    printBinaryTree(root1);

    decode(hasil);

    return 0;
}

*/
