/*	
Program		: Yazid.cpp
Deskripsi	: Body prototype untuk modular modular 
              yang berkaitan dengan Encode dan Decode 
              berdasarkan huffman tree
Dibuat oleh : Yazid Fauzan Prasatria (231511032) 
Kelompok	: 2
Kelas		: 1A
Jurusan     : Teknik Komputer dan Informatika
Prodi       : D3 Teknik Informatika
Angkatan    : 2023/2024
Tanggal		: ...
===============================================*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
#include "Yazid.h"
#include <stdint.h>
#include <stdlib.h>
#include "Reivan.h"
#include "Rindi.h"

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

#include <stdint.h>

void intToAscii(uint32_t num, char* ascii) {
    // Konversi angka ke representasi biner 4 byte
    uint8_t bytes[4];
    bytes[0] = (num >> 24) & 0xFF;
    bytes[1] = (num >> 16) & 0xFF;
    bytes[2] = (num >> 8) & 0xFF;
    bytes[3] = num & 0xFF;

    // Konversi setiap byte ke karakter ASCII
    for (int i = 0; i < 4; i++) {
        ascii[i] = (char)bytes[i];
    }
    ascii[4] = '\0'; // Akhiri string dengan null terminator
}


uint32_t asciiToInt(unsigned char* ascii) {
    // Konversi setiap byte ASCII ke nilai numerik
    uint32_t num = 0;
    num |= ((uint32_t)ascii[0] << 24);
    num |= ((uint32_t)ascii[1] << 16);
    num |= ((uint32_t)ascii[2] << 8);
    num |= ((uint32_t)ascii[3]);

    return num;
}

void tambahkan_isi_file(const char* nama_file_a, const char* nama_file_b) {
    FILE* source_file, * destination_file;
    char buffer[1024];
    size_t bytes_read;

    // Open the source file for reading
    source_file = fopen(nama_file_b, "rb");
    if (source_file == NULL) {
        perror("Error opening source file");
        exit(1);
    }

    // Open the destination file for writing
    destination_file = fopen(nama_file_a, "ab");
    if (destination_file == NULL) {
        perror("Error opening destination file");
        fclose(source_file);
        exit(1);
    }

    // Read from the source file and write to the destination file
    while ((bytes_read = fread(buffer, 1, 1024, source_file)) > 0) {
        fwrite(buffer, 1, bytes_read, destination_file);
    }

    // Close files
    fclose(source_file);
    fclose(destination_file);

    if (remove(nama_file_b) == 1) {
    }
}

void pindahtanpahapus(const char* nama_file_a, const char* nama_file_b) {
    FILE* source_file, * destination_file;
    char buffer[1024];
    size_t bytes_read;

    // Open the source file for reading
    source_file = fopen(nama_file_b, "rb");
    if (source_file == NULL) {
        perror("Error opening source file");
        exit(1);
    }

    // Open the destination file for writing
    destination_file = fopen(nama_file_a, "ab");
    if (destination_file == NULL) {
        perror("Error opening destination file");
        fclose(source_file);
        exit(1);
    }

    // Read from the source file and write to the destination file
    while ((bytes_read = fread(buffer, 1, 1024, source_file)) > 0) {
        fwrite(buffer, 1, bytes_read, destination_file);
    }

    // Close files
    fclose(source_file);
    fclose(destination_file);

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

void encode(char* filename, table huff, char* filedes) {
    FILE* fFile, * Encode, * Result;
    tAddress ptrtree;

    // Open the input file in binary mode
    fFile = fopen(filename, "rb");
    if (fFile == NULL) {
        printf("GAGAL MEMUAT FILE!");
        exit(1);
    }

    // Open the output file in binary write mode
    Encode = fopen("dummy.txt", "wb");
    if (Encode == NULL) {
        printf("GAGAL MEMUAT FILE2!");
        fclose(fFile);
        exit(1);
    }

    // Open the output file in binary write mode
    Result = fopen(filedes, "ab");
    if (Result == NULL) {
        printf("GAGAL MEMUAT FILE2!");
        fclose(fFile);
        exit(1);
    }
    char nama[50];
    ambilnama(filename, nama);
    char path[50];
    sprintf(path,"INPUT/Untuk-di-decode/%s.txt",nama);
    FILE *Result2 = fopen(path,"wb");
    if (Result2 == NULL) {
        printf("GAGAL MEMUAT FILE2!");
        fclose(fFile);
        exit(1);
    }

    unsigned char byteContainer;
    unsigned char buffer = 0;
    int bitCount = 0;
    int frequent = 0;
    int padding = 0;
    uint32_t num;

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
                    frequent++;
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
        padding = bitCount;
        buffer <<= (8 - bitCount);
        fwrite(&buffer, sizeof(unsigned char), 1, Encode);
    }
    fprintf(Result, "%c", padding);





    // Close the files
    fclose(fFile);
    fclose(Encode);
    fclose(Result);
    tambahkan_isi_file(filedes, "dummy.txt");
    pindahtanpahapus(path, filedes);
    fclose(Result2);
    /*
    FILE* budi = fopen(filedes, "rb");
    if (budi == NULL) {
        printf("GAGAL MEMUAT FILE!");
        exit(1);
    }
   
    char a;
    while (fscanf(budi, "%c", &a) == 1) {
        if (fscanf(budi, "%c||", &a) == 1) {
            printf("%d\n", a);
        }
    }
    
    fclose(budi);
    */
}

void baca4byte(const char* filename,unsigned char buffer[4]) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fseek(file, 7, SEEK_CUR);
    // Read four bytes from the file into the buffer
    size_t bytesRead = fread(buffer, sizeof(unsigned char), 4, file);
    if (bytesRead != 4) {
        perror("Error reading from file");
    }

    // Close the file
    fclose(file);
}

void ambilnama(const char* path, char* output) {
    const char* filename_with_ext = strrchr(path, '/');
    if (filename_with_ext != NULL) {
        filename_with_ext++;
    }
    else {
        filename_with_ext = path;
    }

    const char* dot = strrchr(filename_with_ext, '.');
    if (dot != NULL) {
        size_t len = dot - filename_with_ext;
        strncpy(output, filename_with_ext, len);
        output[len] = '\0';
    }
    else {
        strncpy(output, filename_with_ext, 255);
        output[255] = '\0';
    }
}


void decode(char* filename) {
    FILE* Deco = fopen(filename, "rb");
    if (Deco == NULL) {
        perror("Error opening file");
        return;
    }
    char path[255];
    char format[7] = { 0 };
    char namafile[255];

    bacaformat(filename, format);
    ambilnama(filename, namafile);
    sprintf(path, "OUTPUT/Hasil-decode/%s.%s", namafile, format);

    FILE* result = fopen(path, "wb");
    if (result == NULL) {
        perror("Error opening file");
        return;
    }
    unsigned char size[4];
    baca4byte(filename, size);
    uint32_t nsize = asciiToInt(size);
    nAddress root = constructTree(filename);

    fseek(Deco, nsize+4+7, SEEK_CUR);
    unsigned char d = fgetc(Deco);
    int padding = d;
    unsigned char byteContainer;
    unsigned char buffer[8];
    int bitCount = 0;

    nAddress current = root;  
    printBinaryTree(root);

    while (fread(&byteContainer, sizeof(unsigned char), 1, Deco)) {
        // Jika mencapai akhir file, proses bit yang tersisa
        if (feof(Deco)) {
            byteContainer >>= (8 - padding);
        }

        for (int i = 0; i < 8; ++i) {
            buffer[bitCount++] = (byteContainer >> (7 - i)) & 1;

            // Saat buffer penuh atau saat proses terakhir
            while (bitCount == 8|| bitCount == (8-padding) || (feof(Deco) && bitCount > 0)) {
                current = buffer[0] == 0 ? current->left : current->right;
                // Geser buffer dan kurangi bitCount
                for (int j = 1; j < bitCount; ++j) {
                    buffer[j - 1] = buffer[j];
                }
                bitCount--;

                // Jika mencapai leaf node
                if (current->left == NULL && current->right == NULL) {
                    fprintf(result, "%c", current->info);
                    current = root;  
                }

                
            }
        }
    }
    fclose(Deco);
    fclose(result);
}

void bacaformat(const char* filename, char format[7]) {
    FILE* baca = fopen(filename, "rb");
    if (baca == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < 7; i++) {
        int c = fgetc(baca);
        if (c == EOF) {
            format[i] = '\0';
            break;
        }
        format[i] = (char)c;
    }
    fclose(baca);
}