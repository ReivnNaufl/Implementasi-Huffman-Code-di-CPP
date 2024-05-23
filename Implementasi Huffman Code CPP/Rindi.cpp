#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "Reivan.h"

nAddress buildHuffmanTree(qAddress* head) {
    while (next(*head) != NULL) {
        // Extract two nodes with the smallest frequencies
        nAddress left = pNode(*head);
        qAddress temp = *head;
        *head = next(*head);
        free(temp);

        nAddress right = pNode(*head);
        temp = *head;
        *head = next(*head);
        free(temp);

        // Create a new internal node with these two nodes as children
        nAddress newNode = createNode(0);  // The info for internal nodes is not important
        freq(newNode) = freq(left) + freq(right);
        left(newNode) = left;
        right(newNode) = right;

        // Insert the new node back into the queue
        qAddress newQueueNode = createQueueNode(newNode);
        queueInsert(head, newQueueNode);

        // Sort the queue again
        mergeSort(head);
    }

    // The remaining node is the root of the Huffman Tree
    return pNode(*head);
}

void printBinaryTree(node* root, int space, int height) {
    if (root == NULL) {
        return;
    }

    space += height;
    printBinaryTree(right(root), space, height);
    printf("\n");

    for (int i = height; i < space; i++) {
        printf(" ");
    }
    printf("%d", (int)info(root));  // Assuming info is the value you want to print
    printf("\n");
    printBinaryTree(left(root), space, height);
}

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

void printCodes(tAddress codeTable) {
    tAddress p = codeTable;
    while (p != NULL) {
        printf("Byte: %x, Code: %s\n", byte(p), code(p));
        p = next(p);
    }
}
