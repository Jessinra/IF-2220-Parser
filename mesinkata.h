/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "boolean.h"
#include "mesinkar.h"

#define NMax 50
#define BLANK ' '

typedef struct {
	char *TabKata; 
    int Length;
} Kata;

/* State Mesin Kata */
extern boolean EndKata;
extern Kata CKata;
extern int list_of_input[99999];
extern int maxindex;
extern int baris[99999];


int IsSymbol();
/* Check if CC is symbol */

int IsTitikKoma();
/* Check if CC is semi-colon */

int IsAngka();
/* Check if CC is bracket */

int IsKurung();
/* Check if CC is newline */

int IsNewline();
/* Check if CC is number */

void IgnoreBlank();
/* Skip whitespace */

void STARTKATA();
/* Start parse text */

void ADVKATA();
/* Read next word */

void SalinSimbol();
/* Copy symbol */

void SalinAngka();
/* Copy number */

void SalinKata();
/* Copy words */

int CompareKata(Kata Kata1, Kata Kata2);
/* Compare words */

int KataToIndex(Kata K);
/* Change word to token (int) */

void printkata(Kata C);
  /* Show word */

void init_token(char *filename);
/* parse external file contain strings and fill into array as tokens */

char* IndexToToken(int x);
/* Change token (int) to string */

#endif

