#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "macro.h"

node_t* substitute_macro_params (node_t* macro_head, char line[][MAXCN]) {
    node_t* current = macro_head->next, *node, *macro_start, *aux, *temp, *new_node, *previous;
    int line_counter = 0, address_counter = 0;
    char macro_aux[3][MAXCN];
    char aux_line[5][MAXCN] = {{0}};

    while (strcmp(current->label, line[1]) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        return NULL;
    }

    strcpy(macro_aux[0], current->op1);
    strcpy(macro_aux[1], current->op2);
    strcpy(macro_aux[2], current->op3);

    macro_start = current->next;
    previous = macro_head;

    while (strcmp(current->opcode, "ENDMACRO") != 0 && current != NULL) {

        /*SUBSTITUTE FIRST MACRO OP*/
        if (strcmp(current->op1, macro_aux[0]) == 0) {
            strcpy(current->op1, line[2]);
        }
        else if (strcmp(current->op1, macro_aux[1]) == 0) {
            strcpy(current->op1, line[3]);
        }
        else if (strcmp(current->op1, macro_aux[2]) == 0) {
            strcpy(current->op1, line[4]);
        }

        /*SUBSTITUTE SECOND MACRO OP*/
        if (strcmp(current->op2, macro_aux[0]) == 0) {
            strcpy(current->op2, line[2]);
        }
        else if (strcmp(current->op2, macro_aux[1]) == 0) {
            strcpy(current->op2, line[3]);
        }
        else if (strcmp(current->op2, macro_aux[2]) == 0) {
            strcpy(current->op2, line[4]);
        }

        /*SUBSTITUTE THIRD MACRO OP*/
        if (strcmp(current->op3, macro_aux[0]) == 0) {
            strcpy(current->op3, line[2]);
        }
        else if (strcmp(current->op3, macro_aux[1]) == 0) {
            strcpy(current->op3, line[3]);
        }
        else if (strcmp(current->op3, macro_aux[2]) == 0) {
            strcpy(current->op3, line[4]);
        }

        node = in_list(current->opcode, macro_head);
        if (node != NULL) {
            strcpy(aux_line[0], current->label);
            strcpy(aux_line[1], current->opcode);
            strcpy(aux_line[2], current->op1);
            strcpy(aux_line[3], current->op2);
            strcpy(aux_line[4], current->op3);
            aux = substitute_macro_params(macro_head, aux_line);
            macro_start = aux;
            while (strcmp(macro_start->opcode, "ENDMACRO") != 0) {
                new_node = initialize_list(new_node);
                new_node->count = macro_start->count;
                strcpy(new_node->label, macro_start->label);
                strcpy(new_node->opcode, macro_start->opcode);
                strcpy(new_node->op1, macro_start->op1);
                strcpy(new_node->op2, macro_start->op2);
                strcpy(new_node->op3, macro_start->op3);

                previous = add_next_node(previous, new_node);

                // RUNS THROUGH THE BODY OF THE MACRO
                macro_start = macro_start->next;
            }
            temp = current->next;
            free(current);
            memset(current->label, 0, sizeof(current->label));
            previous->next = temp;
            current = previous;
        }
        previous = current;
        current = current->next;
    }

    return macro_start;

}
