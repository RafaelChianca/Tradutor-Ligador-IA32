#ifndef COMMON_H_
  #define COMMON_H_
  #include <stdlib.h>
  #include <stdio.h>
  #include <string.h>
#endif

#ifndef ANALYZER_H_
  #define ANALYZER_H_
  #include "analyzer.h"
#endif

void syntaticAnalyzer(char line[][MAXCN], int *address_counter) {
    int i, opcode_flag = 0, directive_flag = 0, dif_directive_flag = 0, op_int = 0;
    int all_opcodes = 0;
    char *opcode[] = {"ADD","SUB","MULT","DIV","JMP","JMPN","JMPP","JMPZ","LOAD","STORE","INPUT","OUTPUT","C_INPUT","C_OUTPUT","H_INPUT","H_OUTPUT","STOP","COPY","S_INPUT","S_OUTPUT"};
    char *directives[] = {"SECTION", "CONST", "EQU", "IF"};
    char *dif_directives[] = {"END", "SPACE"};

    all_opcodes = inVector(line[1], opcode, 20);
    opcode_flag = inVector(line[1], opcode, 16);
    directive_flag = inVector(line[1], directives, 4);
    dif_directive_flag = inVector(line[1], dif_directives, 2);


    /* ALL OPCODES EXCEPT COPY AND STOP */
    if (opcode_flag) {
        *address_counter += 2;
    }
    /* FOR COPY, S_INPUT, S_OUTPUT */
    if ( (strcmp(line[1], opcode[17]) == 0) || (strcmp(line[1], opcode[18]) == 0) || (strcmp(line[1], opcode[19]) == 0) ) {
        *address_counter += 3;
    }
    /* FOR STOP */
    else if (strcmp(line[1], opcode[16]) == 0 ) {
        *address_counter += 1;
    }

    /* ALL DIRECTIVES EXCEPT END AND SPACE */
    if (directive_flag) {
        if (strcmp(line[1], directives[1]) == 0) {
            *address_counter += 1;
        }
    }
    /* END -> Size 0*/
    if ( (strcmp(line[1], dif_directives[0]) == 0) ) {
        *address_counter += 0;
    }

    /*SPACE -> Variable Size*/
    if ( (strcmp(line[1], dif_directives[1]) == 0) ) {
        if (line[2][0] == '\0'  && line[3][0] == '\0' && line[4][0] == '\0') {
            *address_counter += 1;
        }
        if (line[2][0] != '\0'  && line[3][0] == '\0' && line[4][0] == '\0') {
            op_int = atoi(line[2]);
            *address_counter += op_int;
        }
    }
}

bool inVector(char *needle, char *haystack[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        if(strcmp(haystack[i], needle) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}
