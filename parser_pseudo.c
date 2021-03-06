
#include "parser_pseudo.h"
#include "mesinkata.h"
#include <stdio.h>

int main (void){

    Token current_input;
    int current_state;
    int current_input_index_on_list = 0;
    int row, col;
    TABLE table_value;
    char filename[30];


    /* Getting name of file which will be parsed */
    printf("Input file name: "); scanf("%s", &filename);
    printf("Compiling \"%s\"...\n\n", filename);


    /* Initialize array of input (list_of_input)*/
    init_token(filename);

    /* Initialize parse table */
    PARSE_TABLE parse_table;
    init_table(parse_table);

    /* Initialize rules */
    RULES list_of_rules;
    init_grammar(list_of_rules);

    /* Initialize stack */
    Stack main_stack;
    CreateEmpty(&main_stack);
    Stack_elmt stack_input, stack_output;

    /* Bottom of stack */
    SState(stack_input) = 0;
    SToken(stack_input) = 0;
    Push(&main_stack, stack_input);


    /* Repeat until break */
    while(1){

        Print_derivation(main_stack);

        /* Get information of current processed input , and current state */
        current_input = Token(list_of_input, current_input_index_on_list);
        current_state = SState(InfoTop(main_stack));

        /* Evaluate current input and current_state in table */
        row = current_state;
        col = current_input;
        table_value = Parse_elmt(parse_table, row, col);


        /* Shift */
        if(Act(table_value) == 's'){

            /* preparing to push input, and new current state into stack */
            SToken(stack_input) = current_input;
            SState(stack_input) = State(table_value);

            /* Push as one element */
            Push(&main_stack, stack_input);

            /* Increment list of input index */
            current_input_index_on_list += 1;
        }

        /* Reduce using rules */
        else if(Act(table_value) == 'r'){

            /* Search for lhs and rhs length in array of rules */
            int LHS = Grm(GRAMMAR(list_of_rules, State(table_value)));
            int RHS_length = Len(GRAMMAR(list_of_rules, State(table_value)));

            /* Popping stack (as one element) ~ */
            int j;
            for(j = 1; j <= (RHS_length); j++){

                Pop(&main_stack, &stack_output);
            }

            /* Get current state */
            current_state = SState(InfoTop(main_stack));
            
            /* Evaluate LHS and current_state in table */
            row = current_state;
            col = LHS;
            table_value = Parse_elmt(parse_table, row, col);

            /* Check if evaluation failed */
            if(Act(table_value) == '0'){

                printf("Compile failed...\n");
                Write_error_message(current_input, current_input_index_on_list);
                break;
            }

            /* preparing to push (LHS & new state) into stack again */
            SToken(stack_input) = LHS;
            SState(stack_input) = State(table_value);

            /* Push to stack */
            Push(&main_stack, stack_input);
        }

        /* Accept */
        else if(Act(table_value) == 'a'){

            printf("\n\n\n\nCompile success ! \\ (^.^)/ \n\n");
            break;
        }

        /* Null in parse table */
        else {
            printf("\n\n\n\nCompile failed...\n");
            Write_error_message(current_input, current_input_index_on_list);
            break;
        }
    }

    system("pause");
    return 0;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~       Additional function             ~~~~~~~~~~~~~~~~~~ */


void Write_error_message(Token current_input,int current_index){
    /* Display error message */

    if (current_input == 9){

        /* 'semicolon' is not inserted into baris[] */
        printf("Syntax error occured on line %d\n", baris[current_index-1]);
    }

    else{
        printf("Syntax error occured on line %d\n", baris[current_index]);
    }
}

void Print_token_list(Array_token list_of_input, int amount){
    /* Display list of input */

    int i;
    for (i = 0; i <= amount; i++){
        printf("token %d : %d, at row %d\n",i+1,list_of_input[i],baris[i]);
    }
}


void Print_derivation(Stack S){
    /* Display parsing derivation */

    int i;

    for (i = Top(S); i > 0; i--){
        printf("%s : %d, ",IndexToToken(SToken(S.T[i])), SState(S.T[i]));
    }
    printf("\n\n");
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~       Stack's  ADT            ~~~~~~~~~~~~~~~~~~ */

void CreateEmpty (Stack *S){
    /* Create empty stack */

    Top(*S) = Nil;
}

boolean IsEmpty (Stack S){
    /* Function to check if stack is emtpy */

    return Top(S) == Nil;
}


void Push (Stack * S, Stack_elmt X){
    /* Function to add element to stack */

    if (IsEmpty(*S)){
        Top(*S) = 1;
    }

    else {
        Top(*S) += 1;
    }

    InfoTop(*S) = X;
}

void Pop (Stack * S, Stack_elmt * X){
    /* Function to remove element from stack */

    *X = InfoTop(*S);

    if (Top(*S) == 1){
        CreateEmpty(S);
    }

    else{
        Top(*S) -= 1;
    }
}

void PrintStack(Stack S){
    /* Function to print stack */

    int i;

    for (i = Top(S); i > 0; i--){
        printf("%d -> token : %d state : %d",i, SToken(S.T[i]), SState(S.T[i]));

        if (i == Top(S)){
            printf("<top>");
        }

        printf("\n\n");
    }
}
