#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
#include "Yazid.h"

int binerKeDesimal(const char* biner) {
    int desimal = 0;
    int panjang = strlen(biner);
    for (int i = 0; i < panjang; ++i) {
        if (biner[panjang - i - 1] == '1') {
            desimal += pow(2, i);
        }
    }
    return desimal;
}

void desimalKeBiner(int desimal, char* biner) {
    int i = 0;
    while (desimal > 0) {
        biner[i++] = (desimal % 2) + '0';
        desimal /= 2;
    }
    biner[i] = '\0';

    // Membalik string biner
    int len = strlen(biner);
    for (int j = 0; j < len / 2; j++) {
        char temp = biner[j];
        biner[j] = biner[len - j - 1];
        biner[len - j - 1] = temp;
    }
}



bool Compare(qAddress head, table man) {
    //deklarasi var dan insialisasi
    qAddress ptrgbr = head;
    tAddress ptrtree = man.next;

    while (ptrgbr != NULL) {//jika belum akhir queue
        ptrtree = man.next;
        while (ptrtree != NULL) {
            if (info(pNode(ptrgbr)) == man.byte) {//jika info sama dengan check
                return true;
            }
            else {
                
                ptrtree = next(ptrtree);
            }
       }
        ptrgbr = next(ptrgbr);
    }
    return false;
}

void binaryToAscii(const char* binaryString, char* asciiString) {
    int length = strlen(binaryString);
    int remainder = length % 8;

    // Jika panjang binaryString tidak merupakan kelipatan dari 8, tambahkan nol di akhir
    if (remainder != 0) {
        int padding = 8 - remainder;
        char* paddedBinaryString = (char*)malloc(length + padding + 1); // +1 untuk null-terminator
        strcpy(paddedBinaryString, binaryString);
        for (int i = 0; i < padding; i++) {
            paddedBinaryString[length + i] = '0';
        }
        paddedBinaryString[length + padding] = '\0'; // Null-terminate the padded string
        binaryString = paddedBinaryString;
        length += padding;
    }

    char byte[9];
    int index = 0;

    for (int i = 0; i < length; i += 8) {
        strncpy(byte, binaryString + i, 8);
        byte[8] = '\0'; // Null-terminate the byte string

        // Convert binary string to integer (ASCII code)
        char asciiChar = (char)strtol(byte, NULL, 2);

        // Store the ASCII character in the output string
        asciiString[index++] = asciiChar;
    }

    asciiString[index] = '\0'; // Null-terminate the ASCII string

    // Free the paddedBinaryString if it was allocated
    if (remainder != 0) {
        free((char*)binaryString);
    }
}

void encode(char* filename, table huff) {
    FILE* fFile, * Encode;
    tAddress ptrtree;

    // Open the input file in binary mode
    fFile = fopen(filename, "rb");
    if (fFile == NULL) {
        printf("GAGAL MEMUAT FILE!");
        exit(1);
    }

    // Open the output file in binary write mode
    Encode = fopen("hasil.txt", "wb");
    if (Encode == NULL) {
        printf("GAGAL MEMUAT FILE2!");
        fclose(fFile);
        exit(1);
    }

    unsigned char byteContainer;
    unsigned char buffer = 0;
    int bitCount = 0;

    // Read the input file byte by byte
    while (fread(&byteContainer, sizeof(unsigned char), 1, fFile)) {
        ptrtree = huff.next;
        // Traverse the Huffman table to find the code for the byte
        while (ptrtree != NULL) {
            if (byteContainer == ptrtree->byte) {
                // Write the corresponding Huffman code to the output file
                char* code = ptrtree->code;
                for (int i = 0; code[i] != '\0'; ++i) {
                    buffer <<= 1;
                    if (code[i] == '1') {
                        buffer |= 1;
                    }
                    bitCount++;

                    // If we have collected 8 bits, write the byte to the file
                    if (bitCount == 8) {
                        fwrite(&buffer, sizeof(unsigned char), 1, Encode);
                        bitCount = 0;
                        buffer = 0;
                    }
                }
                break;
            }
            ptrtree = ptrtree->next;
        }
    }

    // Write any remaining bits (if any)
    if (bitCount > 0) {
        buffer <<= (8 - bitCount);
        fwrite(&buffer, sizeof(unsigned char), 1, Encode);
    }

    // Close the files
    fclose(fFile);
    fclose(Encode);
}