#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "convert.h"


node_t* translate(node_t* head) {
    char *opcode[] = {"ADD","SUB","MULT","DIV","JMP","JMPN","JMPP","JMPZ","COPY","LOAD","STORE","INPUT","OUTPUT","C_INPUT","C_OUTPUT","H_INPUT","H_OUTPUT","S_INPUT","S_OUTPUT","STOP", "\0"};
    char *directives[] = {"SECTION", "SPACE", "CONST", "EQU", "IF", "\0"};
    node_t* ia_32_head = initialize_list(ia_32_head);
    node_t* node;
    node_t* data_node;
    node_t *current = head->next;
    int i = 0, j = 0;
        while (current != NULL) {
            i = in_array(current->opcode, opcode);
            if (i == -1) {
                j = in_array(current->opcode, directives);
            }
            if (i != -1) {
                switch (i) {
                    case 1: /*ADD*/
                        ia_32_head = add_line(ia_32_head, current->label, "ADD", "EAX", current->op1, "", current->count, current->address);
                    break;
                    case 2: /*SUB*/
                        ia_32_head = add_line(ia_32_head, current->label, "SUB", "EAX", current->op1, "", current->count, current->address);
                    break;
                    case 3: /*MULT*/
                        ia_32_head = add_line(ia_32_head, current->label, "IMUL", current->op1, "", "", current->count, current->address);
                    break;
                    case 4: /*DIV*/
                    break;
                    case 5: /*JMP*/
                        ia_32_head = add_line(ia_32_head, current->label, "JMP", current->op1, "", "", current->count, current->address);
                    break;
                    case 6: /*JMPN*/
                        ia_32_head = add_line(ia_32_head, current->label, "CMP", "0", "EAX", "", current->count, current->address);
                        ia_32_head = add_line(ia_32_head, "", "JL", current->op1, "", "", current->count+1, current->address+2);
                    break;
                    case 7: /*JMPP*/
                        ia_32_head = add_line(ia_32_head, current->label, "CMP", "EAX", "0", "", current->count, current->address);
                        ia_32_head = add_line(ia_32_head, "", "JG", current->op1, "", "", current->count+1, current->address+2);
                    break;
                    case 8: /*JMPZ*/
                        ia_32_head = add_line(ia_32_head, current->label, "CMP", "EAX", "0", "", current->count, current->address);
                        ia_32_head = add_line(ia_32_head, "", "JE", current->op1, "", "", current->count+1, current->address+2);
                    break;
                    case 9: /*COPY*/
                        ia_32_head = add_line(ia_32_head, current->label, "MOV", current->op2, current->op1, "", current->count, current->address);
                    break;
                    case 10: /*LOAD*/
                        ia_32_head = add_line(ia_32_head, current->label, "MOV", "EAX", current->op1, "", current->count, current->address);
                    break;
                    case 11: /*STORE*/
                        ia_32_head = add_line(ia_32_head, current->label, "MOV", current->op1, "EAX", "", current->count, current->address);
                    break;
                    case 12: /*INPUT*/
                        ia_32_head = add_line(ia_32_head, "", "PUSH", current->op1, "", "", current->count, current->address);
                        ia_32_head = add_line(ia_32_head, "", "CALL", "LerInteiro", "", "", current->count+1, current->address);
                    break;
                    case 13: /*OUTPUT*/
                        ia_32_head = add_line(ia_32_head, "", "PUSH", current->op1, "", "", current->count, current->address);
                        ia_32_head = add_line(ia_32_head, "", "CALL", "EscreverInteiro", "", "", current->count+1, current->address);
                    break;
                    case 14: /*C_INPUT*/
                        ia_32_head = add_line(ia_32_head, "", "PUSH", current->op1, "", "", current->count, current->address);
                        ia_32_head = add_line(ia_32_head, "", "CALL", "LerChar", "", "", current->count+1, current->address);
                    break;
                    case 15: /*C_OUTPUT*/
                        ia_32_head = add_line(ia_32_head, "", "PUSH", current->op1, "", "", current->count, current->address);
                        ia_32_head = add_line(ia_32_head, "", "CALL", "EscreverChar", "", "", current->count+1, current->address);
                    break;
                    case 16: /*H_INPUT*/
                        ia_32_head = add_line(ia_32_head, "", "PUSH", current->op1, "", "", current->count, current->address);
                        ia_32_head = add_line(ia_32_head, "", "CALL", "LerHexa", "", "", current->count+1, current->address);
                    break;
                    case 17: /*H_OUTPUT*/
                        ia_32_head = add_line(ia_32_head, "", "PUSH", current->op1, "", "", current->count, current->address);
                        ia_32_head = add_line(ia_32_head, "", "CALL", "EscreverHexa", "", "", current->count+1, current->address);
                    break;
                    case 18: /*S_INPUT*/
                        ia_32_head = add_line(ia_32_head, "", "PUSH", current->op1, "", "", current->count, current->address);
                        ia_32_head = add_line(ia_32_head, "", "CALL", "LerString", "", "", current->count+1, current->address);
                    break;
                    case 19: /*S_OUTPUT*/
                        ia_32_head = add_line(ia_32_head, "", "PUSH", current->op1, "", "", current->count, current->address);
                        ia_32_head = add_line(ia_32_head, "", "CALL", "EscreverString", "", "", current->count+1, current->address);
                    break;
                    case 20: /*STOP*/
                        ia_32_head = add_line(ia_32_head, "", "MOV", "EAX", "1", "", current->count, current->address);
                        ia_32_head = add_line(ia_32_head, "", "MOV", "EBX", "0", "", current->count+1, current->address);
                        ia_32_head = add_line(ia_32_head, "", "INT 80h", "", "", "", current->count+2, current->address);
                    break;
                }
            }
            else if (j != -1) {
                switch (j) {
                    case 1: /*SECTION*/
                        if(strcmp(current->op1, "TEXT") == 0) {
                            ia_32_head = add_line(ia_32_head, "", "SECTION", ".TEXT", "", "", current->count, current->address);
                            ia_32_head = add_line(ia_32_head, "", "_start:", "", "", "", current->count+1, current->address);

                        }
                        else if(strcmp(current->op1, "DATA") == 0) {
                            data_node = create_node("", "SECTION", ".DATA", "", "", current->count, current->address);
                            data_node->next = ia_32_head->next;
                            ia_32_head->next = data_node;

                        }
                    break;
                    case 2: /*SPACE*/
                        if (strcmp(current->op1, "") != 0) {
                            j = atoi(current->op1);
                            memset(current->op1, 0, sizeof(current->op1));
                            for (int k = 0; k < j; k++) {
                                strcat(current->op1, "0,");
                            }
                            strcpy(current->op1 + (strlen(current->op1)-1), "\0");
                        } else {
                            strcpy(current->op1, "0");
                        }
                        node = create_node(current->label, "DD", current->op1, "", "", current->count, current->address);
                        data_node = add_next_node(data_node, node);
                    break;
                    case 3: /*CONST*/
                        node = create_node(current->label, "DD", current->op1, "", "", current->count, current->address);
                        data_node = add_next_node(data_node, node);
                    break;
                    case 4: /*EQU*/
                        node = create_node(current->label, current->opcode, current->op1, "", "", current->count, current->address);
                        data_node = add_next_node(data_node, node);
                    break;
                    case 5: /*IF*/
                    break;
                }
            }

            current = current->next;
        }
        write_in_file(ia_32_head, "ia_32");
        return ia_32_head;
}

int in_array(char *needle, char *haystack[]) {
    int i = 0;
    while (haystack[i] != "\0") {
        if(strcmp(haystack[i], needle) == 0) {
            return i + 1;
        }
        ++i;
    }
    return -1;
}
