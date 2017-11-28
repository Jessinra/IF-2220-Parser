/* File: mesinkar.c */
/* Implementasi Mesin Karakter */

#include "mesinkar.h"
#include <stdio.h>

char CC;        
boolean EOP;    

static FILE * pita;
static int retval;

char uncapitalize(char c){
	/* Change capital letter into lower letter */

  	if(c >= 65 && c <= 90){
    	return( c+32 );
	}
	else{
	    return c;
	}
}

void START(char *filename) {
/*  Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
    Karakter pertama yang ada pada pita posisinya adalah pada jendela.
    I.S. : sembarang
    F.S. : CC adalah karakter pertama pada pita. Jika CC != MARK maka EOP akan padam (false).
          Jika CC = MARK maka EOP akan menyala (true) */

	pita = fopen(filename,"a");
	retval = fprintf(pita,"~");
	fclose(pita);
	pita = fopen(filename,"r");
	ADV();
}

void ADV() {
	/* Read next char */

	retval = fscanf(pita,"%c",&CC);
	CC = uncapitalize(CC);
	EOP = (CC == MARK);
	if (EOP) {
		fclose(pita);
	}
}
