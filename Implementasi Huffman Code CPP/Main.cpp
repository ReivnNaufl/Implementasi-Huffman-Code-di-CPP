/*	
Program		: Main.cpp
Deskripsi	: Driver / main program untuk ADT Huffman Code pada kompresi gambar
Dibuat oleh :
            - Muhammad Reivan Naufal Mufid 	(231511021) 
            - Rindi Indriani 		        (231511030) 
            - Yazid Fauzan Prasatria 		(231511032)
Kelompok	: 2
Kelas		: 1A
Jurusan     : Teknik Komputer dan Informatika
Prodi       : D3 Teknik Informatika
Angkatan    : 2023/2024
Tanggal		: 15 Mei 2023
===============================================*/

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
        choice = mainMenu(); //panggil main menu
        switch (choice) 
        {
            case 1://encode
                //buat yser menginput nama file
                system("cls");
                printf("Masukan nama file (dengan ekstensi) yang akan di encode: ");
                scanf(" %s", fileName);

                //buat path dari nama file
                sprintf(filePath, "INPUT/Untuk-di-encode/%s", fileName);
                system("cls");

                //baca file, susun dan sort list
                head = createList(filePath);
                mergeSort(&head);

                //biat huffman tree
                root = buildHuffmanTree(&head);
                printf("Huffman Tree:\n");
                printBinaryTree(root);

                //henerate huffman code
                generateCodes(root, code, 0, &codeTable);
                printf("Huffman Codes:\n");
                printCodes(codeTable.next);

                //print bagian header ke encoded file
                encodedPath = fprintHeader(fileName, root);

                //encode isi file
                encode(filePath, codeTable, encodedPath);

                //campare size original dan encoded file
                compare(filePath, encodedPath);

                printf("Tekan tombol apapun untuk melanjutkan ");
                getch();

                //dealloc table and tree
                deallocateTree(root);
                deallocateTable(codeTable.next);
                free(encodedPath);

                // Print confirmation messages
                printf("Tree dan table telah didealokasi.\n");

                // Reset pointers
                root = NULL;
                codeTable.next = NULL;

                break;
            case 2://decode
                //buat user menginput nama file
                system("cls");
                printf("Masukan nama file (dengan ekstensi) yang akan di decode: ");
                scanf(" %s", fileName);
                
                //buat path dari nama file
                sprintf(filePath, "INPUT/Untuk-di-decode/%s", fileName);
                system("cls");

                //decode file
                decode(filePath);

                printf("Decode selesai!\n\n");
                printf("Tekan tombol apapun untuk melanjutkan ");
                getch();

                break;
            case 3://help
                system("cls");

                printf("Encode:\n");
                printf("\t1. Masukan file yang ingin di encode ke direktori INPUT/Untuk-di-encode/\n");
                printf("\t2. Di main menu pilih menu encode dan masukan nama file beserta ekstensinya\n");
                printf("\t3. Tunggu program berhasil mengencode, lama proses ini tergantung dari besar file\n");
                printf("\t4. Hasil encode akan disimpan di direktori OUTPUT/Hasil-encode/\n\n");

                printf("Decode:\n");
                printf("\t1. Masukan file yang ingin di decode ke direktori INPUT/Untuk-di-decode/\n");
                printf("\t2. Di main menu pilih menu decode dan masukan nama file beserta ekstensinya\n");
                printf("\t3. Tunggu program berhasil mendecode, lama proses ini tergantung dari besar file\n");
                printf("\t4. Hasil encode akan disimpan di direktori OUTPUT/Hasil-decode/\n\n\n");

                printf("Tekan tombol apapun untuk melanjutkan ");
                getch();
                
                break;
            case 4://quit
                return 0;
        }
    }
}