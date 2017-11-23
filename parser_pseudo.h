
#ifndef LR_PARSER_H
#define LR_PARSER_H

/* Used constant */
#define Max_row 250
#define Max_col 75
#define Max_rules 75
#define Max_token 300
#define Max_stack 300

/* Defining boolean */
#define boolean unsigned char
#define true 1
#define false 0
#define Nil 0

/* Library */
#include <stdio.h>
#include <stdlib.h>


/* =================     Type definition      =================*/
typedef short Token;

typedef struct {
    short LHS;
    short RHS_len;
} Rules;
#define Lhs(R) (R).LHS
#define Rhs_len(R) (R).RHS_len




typedef struct {
    char action;
    short state;
} Table_elmt;
#define Act(T) (T).action
#define State(T) (T).state






typedef Token Array_token[Max_token+1];
#define Token(T, i) (T)[(i)]




typedef Table_elmt Parse_table[Max_row+1][Max_col+1];
#define Parse_elmt(T, i, j) (T)[(i)][(j)]




typedef Rules Array_rules[Max_rules+1];
#define Rules(T, i) (T)[(i)]



typedef struct {
    short state;
    Token token;
} Stack_elmt;
#define SState(S) (S).state
#define SToken(S) (S).token



typedef struct Stack{
	Stack_elmt T[Max_stack+1]; /* tabel penyimpan elemen */
	int TOP;  /* alamat TOP: elemen puncak */
} Stack;
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]


/* =====================         ADT STACK         ===================== */

void CreateEmpty (Stack *S);

boolean IsEmpty (Stack S);

void Push (Stack * S, Stack_elmt X);

void Pop (Stack * S, Stack_elmt* X);

void PrintStack(Stack S);


#endif
