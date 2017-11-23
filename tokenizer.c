/*
----------------- External File Tokenizer -----------------------
--------------------- IF2220 - TBFO ----------------------------- 
Anggota Kelompok : 
1. M. Aditya Farizki	13516082
2. Shandy				13516097
3. Jessin				13516112

 */

/* Include libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* nama program */
#define filename "program.txt"

int main(){

	FILE *fin;
	char str[100]; /* menampung pembacaan tiap baris file */
	char* arrtoken[100]; /* array of string, menampung token */
	char *delimiter = " \t\n";
	char *token;
	int neff = 0;
	int i;

	fin = fopen(filename, "r");
	
	/* transversal file hingga akhir file dengan membaca per baris */
	while(fgets(str, sizeof(str), fin)) {
		/* ambil token pertama dari baris */
		token = strtok(str, delimiter);

		while(token != NULL) {
			arrtoken[neff] = malloc(strlen(token)+1); /* alokasi memori untuk token */
			strncpy(arrtoken[neff], token, strlen(token)); /* copy string dari token ke arrtoken */
			neff++;
			token = strtok(NULL, delimiter); /* pindah ke kata berikutnya dalam satu baris */
		}
	}

	arrtoken[neff] = NULL;
	fclose(fin);

	printf("\n\n----------------------------\n\n");

	/* print arrtoken */
	for(i=0;i<neff;i++){
		printf("%2d. %s\n", i, arrtoken[i]);
	}

	return 0;
}
