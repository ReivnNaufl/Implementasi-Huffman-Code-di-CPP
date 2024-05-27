#include <stdio.h>
#include <ctype.h>
#include "Reivan.h"
#include "Rindi.h"
#include "Yazid.h"
#include <Windows.h>
#include <stdlib.h>
#include <stdint.h>


int main() {
    // Step 1: Create a list from the input file
    qAddress head = createList((char*)"INPUT/Untuk-di-encode/test2.bmp");
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

    char* hasil = fprintHeader((char*)"test2.bmp", root);

    encode((char*)"INPUT/Untuk-di-encode/test2.bmp", codeTable,hasil);

    FILE* tree = fopen("tree.txt", "wb");

    fprintPreOrder(root,tree);

    unsigned char buffer[4];

    baca4byte(hasil, buffer);
    
    uint32_t num = asciiToInt(buffer);

    printf("%d", num );

    nAddress root1 = constructTree(hasil);
    printf("\n\n");
    printBinaryTree(root1);

    decode((char*)"OUTPUT/Hasil-encode/test2.txt");

    return 0;
}
