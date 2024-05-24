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



char* binary_to_ascii(const char* binary_string) {
    size_t len = strlen(binary_string);
    if (len % 8 != 0) {
        // Calculate the number of zeros needed to make the length a multiple of 8
        size_t padding = 8 - (len % 8);
        // Allocate memory for the padded binary string
        char* padded_binary = (char*)malloc(len + padding + 1);
        if (padded_binary == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return NULL;
        }
        // Copy the original binary string to the padded string
        strcpy(padded_binary, binary_string);
        // Append the required number of zeros to the end
        strcat(padded_binary, "00000000" + padding);
        len += padding; // Update the length
        // Display a message about the padding
        // Use the padded binary string for further processing
        binary_string = padded_binary;
    }

    size_t ascii_len = len / 8;
    char* ascii_string = (char*)malloc(ascii_len + 1);
    if (ascii_string == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    for (size_t i = 0; i < ascii_len; ++i) {
        char byte[9] = { 0 };
        strncpy(byte, binary_string + i * 8, 8);
        ascii_string[i] = (char)strtol(byte, NULL, 2);
    }
    ascii_string[ascii_len] = '\0';

    return ascii_string;
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
    char padding = 0; // Variabel untuk menyimpan jumlah padding

    // Read the input file byte by byte
    // Initialize frequent to 0
    int frequent = 0;

    // Initialize bin to an empty string
    size_t binSize = 1024;
    char* bin = (char*)malloc(binSize * sizeof(char));
    if (bin == NULL) {
        perror("Memory allocation failed");
        fclose(fFile);
        fclose(Encode);
        exit(EXIT_FAILURE);
    }
    bin[0] = '\0';


    while (fread(&byteContainer, sizeof(unsigned char), 1, fFile)) {
        ptrtree = huff.next;
        // Traverse the Huffman table to find the code for the byte
        while (ptrtree != NULL) {
            if (byteContainer == ptrtree->byte) {
                // Check if bin needs to be resized
                size_t newLength = strlen(bin) + strlen(ptrtree->code) + 1;
                if (newLength >= binSize) {
                    binSize *= 2;
                    bin = (char*)realloc(bin, binSize * sizeof(char));
                    if (bin == NULL) {
                        perror("Memory reallocation failed");
                        fclose(fFile);
                        fclose(Encode);
                        exit(EXIT_FAILURE);
                    }
                }
                strcat(bin, ptrtree->code);

                // Write the corresponding Huffman code to the output file
                char* code = ptrtree->code;
                for (int i = 0; code[i] != '\0'; ++i) {
                    buffer <<= 1;
                    if (code[i] == '1') {
                        buffer |= 1;
                    }
                    bitCount++;
                    frequent++;
                    // If we have collected 8 bits, write the byte to the file
                    if (bitCount == 8) {
                        //fwrite(&buffer, sizeof(unsigned char), 1, Encode);
                        bitCount = 0;
                        buffer = 0;
                    }
                }
                break;
            }
            ptrtree = ptrtree->next;
        }
    }
    fprintf(Encode, "%c##", frequent);
    ptrtree = huff.next;
    while (ptrtree != NULL) {
        fprintf(Encode, "%s*&", ptrtree->code);
        fprintf(Encode, "%c^^", ptrtree->byte);
        ptrtree = next(ptrtree);
    }
    char* ascii_string = binary_to_ascii(bin);
    fprintf(Encode, "%s", ascii_string);

    // Close the files
    fclose(fFile);
    fclose(Encode);

    // Print the results for debugging
    printf("%d\n", frequent);
    printf("%s\n", bin);



    // Free the allocated memory
    free(bin);
}


void decode(char* filename) {
    table man; 

}