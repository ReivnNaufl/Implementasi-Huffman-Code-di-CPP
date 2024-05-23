#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
#include "Yazid.h"

int binerKeDesimal(const char* biner) {
    int desimal = 0;
    int panjang = 8;
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

void encode(char* filename, table huff) {
    FILE* fFile, * Encode;
    tAddress ptrtree;

    // Open the input file in binary mode
    fFile = fopen(filename, "rb");
    if (fFile == NULL) {
        printf("GAGAL MEMUAT FILE!");
        exit(1);
    }

    char path[256];
    //snprintf(path, sizeof(path), "OUTPUT/Hasil-encode/encoded_%s", filename);

    // Open the output file in write mode
    Encode = fopen("hasil.txt", "w");
    if (Encode == NULL) {
        printf("GAGAL MEMUAT FILE2!");
        fclose(Encode);
        exit(1);
    }

    unsigned char byteContainer;

    // Read the input file byte by byte
    while (fread(&byteContainer, sizeof(unsigned char), 1, fFile)) {
        ptrtree = huff.next;
        // Traverse the Huffman table to find the code for the byte
        while (ptrtree != NULL) {
            if (byteContainer == ptrtree->byte) {
                // Write the corresponding Huffman code to the output file
                int pix;
                pix = binerKeDesimal(ptrtree->code);
                fprintf(Encode, "%c", pix);
                break;
            }
            ptrtree = ptrtree->next;
        }
    }

    // Close the files
    fclose(fFile);
    fclose(Encode);
}