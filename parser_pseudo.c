
#include "parser_pseudo.h"
#include "tabel_parser.h"
#include "mesinkata.h"

int main (void){

    Token current_input;
    int current_state;
    int current_input_index_on_list = 0;
    int row, col;
    TABLE table_value;

    /* Initialize array of input */
    Array_token list_of_input;
    /* initialize */


    /* Initialize parse table */
    PARSE_TABLE parse_table;
    init_table(&parse_table);

    /* Initialize rules */
    RULES list_of_rules;
    init_grammar(&list_of_rules);

    /* Initialize stack */
    Stack main_stack;
    CreateEmpty(&main_stack);
    Stack_elmt stack_input, stack_output;

    /* Bottom of stack */
    SState(stack_input) = 0;
    SToken(stack_input) = '0';
    Push(&main_stack, stack_input);


    /* Repeat until break */
    while(1){

        /* Get information of current processed input , and current state */
        current_input = Token(list_of_input, current_input_index_on_list);
        current_state = SState(InfoTop(main_stack));


        /* Evaluate current input and current_state in table */
        /* COl (CURRENT TOKEN) SUPPOSED TO BE INT SO IT CAN BE DIRECT ACCESSED */
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
            current_input_index_on_list += 1;   // shift to next input
        }

        /* Reduce using rules */
        else if(Act(table_value) == 'r'){

            /* Search for lhs and rhs length in array of rules */
            int LHS = Grm(GRAMMAR(list_of_rules, State(table_value)));
            int RHS_length = Len(GRAMMAR(list_of_rules, State(table_value)));
            /* LHS SHOULD GET CONVERTED INTO INT ASWELL */


            /* Popping stack (as one element) ~ */
            int j;
            for(j = 1; j < (RHS_length); j++){
                Pop(&main_stack, &stack_output);
            }

            /* Get current state */
            current_state = SState(InfoTop(main_stack));

            /* Evaluate LHS and current_state in table */
            row = current_state;
            col = LHS;
            table_value = Parse_elmt(parse_table, row, col);

            /* Check if evaluation failed */
            if(Act(table_value) == '0'){ // table_value.action is un-initialized

                printf("Compile failed...\n");
                /*write_error_message(); */
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

    return 0;
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
