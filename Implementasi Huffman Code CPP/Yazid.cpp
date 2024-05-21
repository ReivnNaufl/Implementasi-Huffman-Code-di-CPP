#include <stdio.h>
#include <string.h>
#include <math.h>
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
