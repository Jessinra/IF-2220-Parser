/* File: mesinkar.c */
/* Implementasi Mesin Karakter */

#include "mesinkar.h"
#include <stdio.h>

char CC;        /* bisa diakses dimana saja */
boolean EOP;    /* bisa diakses dimana saja */

static FILE * pita;
static int retval;

char uncapitalize(char c)
//mengubah huruf besar menjadi huruf kecil
{
      if(c >= 65 && c <= 90){
            return(c+32);
      }
      else{
            return c;
      }
}

void START(char *filename) {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita. Jika CC != MARK maka EOP akan padam (false).
          Jika CC = MARK maka EOP akan menyala (true) */

	/* Algoritma */
    pita = fopen(filename,"a");
    retval = fprintf(pita,"~");
    fclose(pita);
    pita = fopen(filename,"r");
    ADV();
}

void ADV() {
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela =
          CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama,
          CC mungkin = MARK.
		  Jika  CC = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	retval = fscanf(pita,"%c",&CC);
  CC = uncapitalize(CC);
	EOP = (CC == MARK);
	if (EOP) {
       fclose(pita);
 	}
}
