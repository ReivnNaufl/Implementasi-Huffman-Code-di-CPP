#pragma once
#ifndef Yazid_h
#define Yazid_h

#include "struct.h"
#include <stdint.h>

int binerKeDesimal(const char* biner);

void desimalKeBiner(int desimal, char* biner);

void encode(char* filename, table huff,char *filedes);

void binaryToAscii(const char* binaryString, char* asciiString);

void intToAscii(uint32_t num, char* ascii);

uint32_t asciiToInt(unsigned char* ascii);

void baca4byte(const char* filename,unsigned char buffer[4]);

void decode(char* filename);

void bacaformat(const char* filename, char format[7]);

void ambilnama(const char* path, char* output);

#endif