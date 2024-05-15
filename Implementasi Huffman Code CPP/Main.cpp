#include <stdio.h>
#include <ctype.h>
#include "Reivan.h"

int main() {
	queue* head = NULL;

	head = createList((char*)"INPUT/Untuk-di-encode/aae.bmp");
	printList(head);
	
	
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