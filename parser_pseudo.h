
#ifndef LR_PARSER_H
#define LR_PARSER_H

/* Used constant */
#define Max_row 400
#define Max_col 100
#define Max_rules 100
#define Max_token 999
#define Max_stack 999

/* Defining boolean */
#define boolean unsigned char
#define true 1
#define false 0
#define Nil 0

/* Library */
#include <stdio.h>
#include <stdlib.h>


/* =================     Type definition      =================*/

typedef int Token;                               

typedef struct{
	int count;
	int Grammar;                            
} GRAMMAR;
#define Grm(R) (R).Grammar
#define Len(R) (R).count


typedef struct {
    int gotos;
    char action;
} TABLE;
#define Act(T) (T).action
#define State(T) (T).gotos


typedef Token Array_token[Max_token+1];
#define Token(T, i) (T)[(i)]


typedef TABLE PARSE_TABLE[Max_row+1][Max_col+1];
#define Parse_elmt(T, i, j) (T)[(i)][(j)]


typedef GRAMMAR RULES[Max_rules+1];
#define GRAMMAR(T, i) (T)[(i)]


typedef struct {
    int state;
    int token;                           
} Stack_elmt;
#define SState(S) (S).state
#define SToken(S) (S).token


typedef struct Stack{
	Stack_elmt T[Max_stack+1];
	int TOP;
} Stack;
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]


void init_table(PARSE_TABLE M);
/* Initialize parse table */

void init_grammar(RULES G);
/* Initialize grammar table */

void Write_error_message(Token current_input,int current_index);
/* Display error message */

void Print_token_list(Array_token list_of_input, int amount);
/* Display list of input */

void Print_derivation(Stack S);
/* Display parsing derivation */



/* =====================         ADT STACK         ===================== */

void CreateEmpty (Stack *S);
 /* Create empty stack */

boolean IsEmpty (Stack S);
/* Function to check if stack is emtpy */

void Push (Stack * S, Stack_elmt X);
/* Function to add element to stack */

void Pop (Stack * S, Stack_elmt* X);
/* Function to remove element from stack */

void PrintStack(Stack S);
/* Function to print stack */

#endif
