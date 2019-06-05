#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "analyzer.h"


bool lexic_analyzer(char line[][MAXCN]) {
    int i, j, directive_flag = 0;
    char c;
    char *directives[] = {"SECTION", "SPACE", "CONST", "EQU", "IF", "MACRO", "END"};

    /* DIRECTIVES USE NUMBERS AS VALUES */
    for (i = 0; i < 7; i++) {
        if (strcmp(line[1], directives[i]) == 0) {
            directive_flag = 1;
            break;
        }
    }
    /* FIRST CHAR NOT A NUMBER */
    for (i = 0; i < 4; i++) {
        if(line[i][0] >= '0' && line[i][0] <= '9' && !directive_flag) {
            return TRUE;
        }
        /* CHECK THE SCOPE */
        for (j = 1; j < strlen(line[i]); j++) {

            c = line[i][j];
            if ( !( (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || c == '_') ) {
                return TRUE;
            }
        }
    }
    return FALSE;
}


bool syntatic_analyzer(char line[][MAXCN], int *address_counter) {
    int i, opcode_flag, directive_flag, dif_directive_flag, op_int;

    char *opcode[] = {"ADD","SUB","MULT","DIV","JMP","JMPN","JMPP","JMPZ","LOAD","STORE","INPUT","OUTPUT", "COPY", "STOP"};
    char *directives[] = {"SECTION", "CONST", "EQU", "IF"};
    char *dif_directives[] = {"MACRO", "END", "SPACE"};

    opcode_flag = in_vector(line[1], opcode, 12);
    directive_flag = in_vector(line[1], directives, 4);
    dif_directive_flag = in_vector(line[1], dif_directives, 3);

    /* ALL OPCODES EXCEPT COPY AND STOP */
    if (opcode_flag) {
        if (line[2][0] != '\0' && line[3][0] == '\0') {
            *address_counter += 2;
            return FALSE;
        }
        else {
            return TRUE;
        }
    }
    /* FOR COPY */
    if (strcmp(line[1], opcode[12]) == 0) {
        if (line[2][0] != '\0'  && line[3][0] != '\0') {
            *address_counter += 3;
            return FALSE;
        }
        else {
            return TRUE;
        }
    }
    /* FOR STOP */
    else if (strcmp(line[1], opcode[13]) == 0 ) {
        if (line[2][0] == '\0'  && line[3][0] == '\0' ) {
            *address_counter += 1;
            return FALSE;
        }
        else {
            return TRUE;
        }
    }
    else if(!directive_flag && !dif_directive_flag) {
        /* LABEL WITHOUT : AND IS STOP */
        if (line[2][0] != '\0' && line[3][0] == '\0') {
            *address_counter += 1;
            return TRUE;
        }
        else if (line[2][0] != '\0' && line[3][0] != '\0') {
            return TRUE;
        }
    }

    /* ALL DIRECTIVES EXCEPT MACRO, END AND SPACE */
    if (directive_flag) {
        if (line[2][0] != '\0' && line[3][0] == '\0') {
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
    /* MACRO AND END  -> SIZE 0*/
    if ( (strcmp(line[1], dif_directives[0]) == 0) || (strcmp(line[1], dif_directives[1]) == 0) ) {
        if (line[2][0] == '\0'  && line[3][0] == '\0') {
            return FALSE;
        }
        else {
            return TRUE;
        }
    }
    /* SPACE -> VARIABLE SIZE*/
    if ( (strcmp(line[1], dif_directives[2]) == 0) ) {
        if (line[2][0] == '\0'  && line[3][0] == '\0') {
            *address_counter += 1;
            return FALSE;
        }
        if (line[2][0] != '\0'  && line[3][0] == '\0') {
            op_int = atoi(line[2]);
            *address_counter += op_int;
            return FALSE;
        }
        else {
            return TRUE;
        }
    }
}

bool in_vector (char *needle, char *haystack[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        if(strcmp(haystack[i], needle) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}
