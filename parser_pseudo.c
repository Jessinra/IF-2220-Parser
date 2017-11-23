
#include "parser_pseudo.h"

int main (void){

    Token current_input;
    short current_state;
    short current_input_index_on_list = 0;
    short row, col;
    Table_elmt table_value;

    Array_token list_of_input;
    /* initialize list_of_input */ /*(HAS TO BE CHANGED INTO INTEGER)*/

    Parse_table parse_table;
    /* initialize parse_table    */
    /* row  - > state            */
    /* col  - > terminal $ var   */

    Array_rules list_of_rules;
    /* initialize list_of_rules */

    Stack main_stack;
    CreateEmpty(&main_stack);
    Stack_elmt stack_input, stack_output;

    SState(stack_input) = 0;
    Push(&main_stack, stack_input);


    while(1){

        current_input = Token(list_of_input, current_input_index_on_list);
        current_state = SState(InfoTop(main_stack));

        row = current_state;
        col = current_input;

        table_value = Parse_elmt(parse_table, row, col);


        /* Shift */
        if(Act(table_value) == 'S'){

            SToken(stack_input) = current_input;
            Push(&main_stack, stack_input);

            SState(stack_input) = State(table_value);
            Push(&main_stack, stack_input);

            current_input_index_on_list += 1;   // shift to next input
        }

        /* Reduce using rules */
        else if(Act(table_value) == 'R'){

            short LHS = Lhs(Rules(list_of_rules, State(table_value)));
            int RHS_length = Rhs_len(Rules(list_of_rules, State(table_value)));
            /* LHS SHOULD GET CONVERTED INTO SHORT ASWELL */



            /* Popping stack~ */
            int j;
            for(j = 1; j < (RHS_length * 2); j++){
                Pop(&main_stack, &stack_output);
            }

            current_state = SState(InfoTop(main_stack));

            row = current_state;
            col = LHS;
            table_value = Parse_elmt(parse_table, row, col);

            if((Act(table_value) != 'A') && (Act(table_value) != 'S') && (Act(table_value) != 'R')){

                printf("Compile failed...\n");
                /*write_error_message(); */
                break;
            }

            SToken(stack_input) = LHS;
            Push(&main_stack, stack_input);

            SState(stack_input) = State(table_value);
            Push(&main_stack, stack_input);
        }

        /* Accept */
        else if(Act(table_value) == 'A'){

            printf("Compile success ! \\ (^.^)/ \n\n");
            break;
        }

        /* Null in parse table */
        else {
            printf("Compile failed...\n");
            /*write_error_message(); */
            break;
        }
    }
}


/* ==============       ADT STACK        ================= */

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
        printf("%d -> %d ",i, SToken(S.T[i]));

        if (i == Top(S)){
            printf("<top>");
        }

        printf("\n");
    }
}
