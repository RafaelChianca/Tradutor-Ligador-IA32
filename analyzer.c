#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "analyzer.h"
#include "mount.h"

// ERRO SEMANTICO DE ARGUMENTOS DA MACRO SEM '&'
// if (strcmp(line[1], directives[5]) == 0) {
//     for (i = 2; y < 5; i++) {
//         if (line[i][0] != '&') {
//             return TRUE;
//         }
//     }
// }

bool syntatic_analyzer(char line[][MAXCN], int *address_counter) {
    int i, opcode_flag = 0, directive_flag = 0, dif_directive_flag = 0, op_int = 0;
    int all_opcodes = 0;
    char *opcode[] = {"ADD","SUB","MULT","DIV","JMP","JMPN","JMPP","JMPZ","LOAD","STORE","INPUT","OUTPUT", "COPY", "STOP"};
    char *directives[] = {"SECTION", "CONST", "EQU", "IF"};
    char *dif_directives[] = {"MACRO", "END", "SPACE", "ENDMACRO"};

    all_opcodes = in_vector(line[1], opcode, 14);
    opcode_flag = in_vector(line[1], opcode, 12);
    directive_flag = in_vector(line[1], directives, 4);
    dif_directive_flag = in_vector(line[1], dif_directives, 3);


    if(!opcode_flag && !directive_flag && !dif_directive_flag && !all_opcodes) {
        return TRUE;
    }

    /* ALL OPCODES EXCEPT COPY AND STOP */
    if (opcode_flag) {
        *address_counter += 2;
        if (line[2][0] != '\0' && line[3][0] == '\0' && line[4][0] == '\0') {
            return FALSE;
        }
        else {
            return TRUE;
        }
    }
    /* FOR COPY */
    if (strcmp(line[1], opcode[12]) == 0) {
        *address_counter += 3;
        if (line[2][0] != '\0'  && line[3][0] != '\0' && line[4][0] == '\0') {
            return FALSE;
        }
        else {
            return TRUE;
        }
    }
    /* FOR STOP */
    else if (strcmp(line[1], opcode[13]) == 0 ) {
        *address_counter += 1;
        if (line[2][0] == '\0'  && line[3][0] == '\0' && line[4][0] == '\0') {
            return FALSE;
        }
        else {
            return TRUE;
        }
    }
    else if(!directive_flag && !dif_directive_flag) {
        /* LABEL WITHOUT : AND IS STOP */
        if (line[2][0] != '\0' && line[3][0] == '\0' && line[4][0] == '\0') {
            *address_counter += 1;
            return TRUE;
        }
        else if (line[2][0] != '\0' && line[3][0] != '\0' && line[4][0] == '\0') {
            *address_counter += 2;
            return TRUE;
        }
    }

    /* ALL DIRECTIVES EXCEPT MACRO, END AND SPACE */
    if (directive_flag) {
        if (line[2][0] != '\0' && line[3][0] == '\0' && line[4][0] == '\0') {
            /*CHECK IF IS CONST -> SIZE 1*/
            if ((strcmp(line[1], directives[1]) == 0)) {
                *address_counter += 1;
            }
            return FALSE;
        }
        else {
            return TRUE;
        }
    }
    /* ENDMACRO AND END -> SIZE 0*/
    if ( (strcmp(line[1], dif_directives[1]) == 0) || (strcmp(line[1], dif_directives[3]) == 0) ) {
        if (line[2][0] == '\0'  && line[3][0] == '\0' && line[4][0] == '\0') {
            return FALSE;
        }
        else {
            return TRUE;
        }
    }


    if ( (strcmp(line[1], dif_directives[2]) == 0) ) {
        if (line[2][0] == '\0'  && line[3][0] == '\0' && line[4][0] == '\0') {
            *address_counter += 1;
            return FALSE;
        }
        if (line[2][0] != '\0'  && line[3][0] == '\0' && line[4][0] == '\0') {
            op_int = atoi(line[2]);
            *address_counter += op_int;
            return FALSE;
        }
        else {
            return TRUE;
        }
    }
}

int double_check(node_t *head, char* label) {
    node_t* current = head->next;
    int count = 0;

    while(current != NULL) {
        if (strcmp(current->label, label) == 0) {
            count++;
        }
        current = current->next;
    }
    return count;

}


bool in_vector(char *needle, char *haystack[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        if(strcmp(haystack[i], needle) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}
