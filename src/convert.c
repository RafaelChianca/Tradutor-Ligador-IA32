#ifndef COMMON_H_
  #define COMMON_H_
  #include <stdlib.h>
  #include <stdio.h>
  #include <string.h>
#endif
#ifndef CONVERT_H_
  #define CONVERT_H_
  #include "convert.h"
#endif
#ifndef MOUNT_H_
  #define MOUNT_H_
  #include "mount.h"
#endif

node_t* translate(node_t* head, node_t* ia_32_head, int *inputOutputFlags) {
    char *opcode[] = {"ADD","SUB","MULT","DIV","JMP","JMPN","JMPP","JMPZ","COPY","LOAD","STORE","INPUT","OUTPUT","C_INPUT","C_OUTPUT","H_INPUT","H_OUTPUT","S_INPUT","S_OUTPUT","STOP", "\0"};
    char *directives[] = {"SECTION", "SPACE", "CONST", "EQU", "IF", "\0"};
    node_t* node;
    node_t* data_node = NULL;
    node_t *current = head->next;
    int i = 0, j = 0;
        while (current != NULL) {
            i = inArray(current->opcode, opcode);
            if (i == -1) {
                j = inArray(current->opcode, directives);
            }
            if (i != -1) {
                switch (i) {
                    case 1: /*ADD*/
                        alterAddressingMode(current->op1);
                        ia_32_head = addLine(ia_32_head, current->label, "add dword", "eax,", current->op1, "", 2, current->address);
                    break;
                    case 2: /*SUB*/
                        alterAddressingMode(current->op1);
                        ia_32_head = addLine(ia_32_head, current->label, "sub dword", "eax,", current->op1, "", 2, current->address);
                    break;
                    case 3: /*MULT*/
                        alterAddressingMode(current->op1);
                        ia_32_head = addLine(ia_32_head, current->label, "imul dword", current->op1, "", "", 1, current->address);
                    break;
                    case 4: /*DIV*/
                        alterAddressingMode(current->op1);
                        ia_32_head = addLine(ia_32_head, current->label, "idiv dword", current->op1, "", "", 1, current->address);
                    break;
                    case 5: /*JMP*/
                        ia_32_head = addLine(ia_32_head, current->label, "jmp", current->op1, "", "", 5, current->address);
                    break;
                    case 6: /*JMPN*/
                        ia_32_head = addLine(ia_32_head, current->label, "cmp dword", "0,", "eax", "", 4, current->address);
                        ia_32_head = addLine(ia_32_head, "", "jl", current->op1, "", "", 5, current->address+2);
                    break;
                    case 7: /*JMPP*/
                        ia_32_head = addLine(ia_32_head, current->label, "cmp dword", "eax,", "0", "", 4, current->address);
                        ia_32_head = addLine(ia_32_head, "", "jg", current->op1, "", "", 5, current->address+2);
                    break;
                    case 8: /*JMPZ*/
                        ia_32_head = addLine(ia_32_head, current->label, "cmp dword", "eax,", "0", "", 4, current->address);
                        ia_32_head = addLine(ia_32_head, "", "je", current->op1, "", "", 5, current->address+2);
                    break;
                    case 9: /*COPY*/
                        alterAddressingMode(current->op1);
                        alterAddressingMode(current->op2);
                        strcat(current->op2, ",");
                        ia_32_head = addLine(ia_32_head, current->label, "mov dword", "ebx,", current->op1, "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, current->label, "mov dword", current->op2, "ebx", "", 2, current->address);
                    break;
                    case 10: /*LOAD*/
                        alterAddressingMode(current->op1);
                        ia_32_head = addLine(ia_32_head, current->label, "mov dword", "eax,", current->op1, "", 2, current->address);
                    break;
                    case 11: /*STORE*/
                        alterAddressingMode(current->op1);
                        strcat(current->op1, ",");
                        ia_32_head = addLine(ia_32_head, current->label, "mov dword", current->op1, "eax", "", 2, current->address);
                    break;
                    case 12: /*INPUT*/
                        ia_32_head = addLine(ia_32_head, "", "push dword", "eax", "", "", 6, current->address);
                        ia_32_head = addLine(ia_32_head, "", "push dword", current->op1, "", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "call", "LeerInteiro", "", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "pop dword", "eax", "", "", 6, current->address);
                        inputOutputFlags[0] = 1; //LeerInteiro
                        inputOutputFlags[2] = 1; //LeerChar
                    break;
                    case 13: /*OUTPUT*/
                        ia_32_head = addLine(ia_32_head, "", "push dword", "eax", "", "", 6, current->address);
                        ia_32_head = addLine(ia_32_head, "", "push dword", current->op1, "", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "call", "EscreverInteiro", "", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "pop dword", "eax", "", "", 6, current->address);
                        inputOutputFlags[1] = 1; //EscreverInteiro
                        inputOutputFlags[8] = 1; //EscreveEnter
                    break;
                    case 14: /*C_INPUT*/
                        ia_32_head = addLine(ia_32_head, "", "push dword", "eax", "", "", 6, current->address);
                        ia_32_head = addLine(ia_32_head, "", "push dword", current->op1, "", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "call", "LeerChar", "", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "mov dword", "ebx", "esp", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "sub dword", "ebx", "4", "", 2, current->address);
                        inputOutputFlags[2] = 1; //LeerChar
                    break;
                    case 15: /*C_OUTPUT*/
                        ia_32_head = addLine(ia_32_head, "", "push dword", "eax", "", "", 6, current->address);
                        ia_32_head = addLine(ia_32_head, "", "push dword", current->op1, "", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "call", "EscreverChar", "", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "pop dword", "eax", "", "", 6, current->address);
                        inputOutputFlags[3] = 1; //EscreverChar
                        inputOutputFlags[8] = 1; //EscreveEnter
                    break;
                    case 16: /*H_INPUT*/
                        ia_32_head = addLine(ia_32_head, "", "push", current->op1, "", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "call", "LerHexa", "", "", 2, current->address);
                        inputOutputFlags[4] = 1; //LerHexa
                        inputOutputFlags[2] = 1; //LeerChar
                    break;
                    case 17: /*H_OUTPUT*/
                        ia_32_head = addLine(ia_32_head, "", "push", current->op1, "", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "call", "EscreverHexa", "", "", 2, current->address);
                        inputOutputFlags[5] = 1; //EscreverHexa
                        inputOutputFlags[8] = 1; //EscreveEnter
                        inputOutputFlags[9] = 1; //EscreverCharSemEnter
                    break;
                    case 18: /*S_INPUT*/
                        alterAddressingMode(current->op2);
                        ia_32_head = addLine(ia_32_head, "", "push dword", "eax", "", "", 6, current->address);
                        ia_32_head = addLine(ia_32_head, "", "push dword", current->op1, "", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "push dword", current->op2, "", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "call", "LeerString", "", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "pop dword", "eax", "", "", 6, current->address);
                        inputOutputFlags[6] = 1; //LeerString
                        inputOutputFlags[2] = 1; //LeerChar
                    break;
                    case 19: /*S_OUTPUT*/
                        alterAddressingMode(current->op2);
                        ia_32_head = addLine(ia_32_head, "", "push dword", "eax", "", "", 6, current->address);
                        ia_32_head = addLine(ia_32_head, "", "push dword", current->op1, "", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "push dword", current->op2, "", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "call", "EscreverString", "", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "pop dword", "eax", "", "", 6, current->address);
                        inputOutputFlags[7] = 1; //EscreverString
                        inputOutputFlags[8] = 1; //EscreveEnter
                        inputOutputFlags[9] = 1; //EscreverCharSemEnter
                    break;
                    case 20: /*STOP*/
                        ia_32_head = addLine(ia_32_head, "", "mov", "eax,", "1", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "mov", "ebx,", "0", "", 2, current->address);
                        ia_32_head = addLine(ia_32_head, "", "int 80h", "", "", "", 5, current->address);
                    break;
                }
            }
            else if (j != -1) {
                switch (j) {
                    case 1: /*SECTION*/
                        if(strcmp(current->op1, "TEXT") == 0) {
                            ia_32_head = addLine(ia_32_head, "", "global", "_start", "", "", 0, current->address);
                            ia_32_head = addLine(ia_32_head, "", "section", ".text", "", "", 0, current->address);
                            ia_32_head = addLine(ia_32_head, "", "_start:", "", "", "", 0, current->address);

                        }
                        else if(strcmp(current->op1, "DATA") == 0) {
                            if (data_node == NULL) {
                                data_node = createNode("", "section", ".data", "", "", 0, current->address);
                                data_node->next = ia_32_head->next;
                                ia_32_head->next = data_node;
                            }
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
                        node = createNode(current->label, "dd", current->op1, "", "", 0, current->address);
                        data_node = addNextNode(data_node, node);

                    break;
                    case 3: /*CONST*/
                        node = createNode(current->label, "dd", current->op1, "", "", 0, current->address);
                        data_node = addNextNode(data_node, node);

                    break;
                    case 4: /*EQU*/
                        node = createNode(current->label, "dd", current->op1, "", "", 0, current->address);
                        if (data_node == NULL) {
                            data_node = createNode("", "section", ".data", "", "", 0, current->address);
                            data_node->next = ia_32_head->next;
                            ia_32_head->next = data_node;
                        }
                        data_node = addNextNode(data_node, node);

                    break;
                    case 5: /*IF*/
                        alterAddressingMode(current->op1);
                        strcat(current->op1, ",");
                        ia_32_head = addLine(ia_32_head, "", "cmp dword", current->op1, "1", "", 0, current->address);
                        if (strcmp(current->next->next->label, "") == 0) {
                            strcpy(current->next->next->label, "jump");
                            ia_32_head = addLine(ia_32_head, "", "jne", "jump", "", "", 5, current->address);
                        } else {
                            ia_32_head = addLine(ia_32_head, "", "jne", current->next->next->label, "", "", 5, current->address);
                        }
                    break;
                }
            }
            current = current->next;
        }
        return ia_32_head;
}

int inArray(char *needle, char *haystack[]) {
    int i = 0;
    while (haystack[i] != "\0") {
        if(strcmp(haystack[i], needle) == 0) {
            return i + 1;
        }
        ++i;
    }
    return -1;
}

void alterAddressingMode(char *op) {
    long integer;
    int size, i;
    char newOp[MAXCN] = "[";
    char number[MAXCN];
    char *token, op_aux[MAXCN];

    if(strcmp(op, "") != 0) {

        strcpy(op_aux, op);
        size = strlen(op);
        token = strtok(op, "+");
        strcat(newOp, token);

        for (i = 0; i < size; i++) {
            if (op_aux[i] == '+') {
                strcat(newOp, " + ");
                token = strtok(NULL, "+");
                integer = atoi(token) * 4;
                sprintf(token, "%ld", integer);
                strcat(newOp, token);
            }
        }
        strcat(newOp, "]");
        strcpy(op, newOp);
    }

}
