#include <stdio.h>
#include <ctype.h>
#include "Reivan.h"
#include "Rindi.h"

int main() {
    // Step 1: Create a list from the input file
    qAddress head = createList((char*)"INPUT/Untuk-di-encode/aae.bmp");
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

    return 0;
}




/*

int main() {
	int i = 0;
	infotype bit = 0x00;
	unsigned char* bite;
	FILE* fBmp, *fCreate;
	int fileLen = 0;
	fBmp = fopen("aae.bmp", "rb");
	fCreate = fopen("create.bmp", "w");
	while (!feof(fBmp)) {
		bit= fgetc(fBmp);
		fprintf(fCreate, "%c", bit);
		fileLen++;
	}
	/*rewind(fBmp);
	fseek(fBmp, 0, SEEK_END);
	fileLen = ftell(fBmp);
	rewind(fBmp);
	bite = (unsigned char*)malloc(fileLen * sizeof(char));
	fread(bite, fileLen, 1, fBmp);
	fclose(fBmp);
	fclose(fCreate);
}

*/