#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "mount.h"


void mount_program(node_t *head) {
    node_t *label_head;
    char addr[MAXCN];
    node_t *current = head->next;
    int label_flag = 0;
    label_head = initialize_list(label_head);
    label_head = make_label_addr_list(label_head, head);
    printf("\n****************************************************************\n");
    printf("\t\t\tLABELS FOUND");
    print_list(label_head);
    printf("*****************************************************************\n");

    while(current != NULL) {
        /*IT'S NOT EMPTY AND IT'S NOT A NUMBER*/
        if(current->op1 && !is_numeric(current->op1)) {
            label_flag = is_label_in_list(current->op1, label_head);
            if(label_flag != -1) {
                memset(current->op1, 0, sizeof(current->op1));
                sprintf(addr, "%d", label_flag);
                /*TURN THE ADDRESS NUMBER INTO A STRING*/
                strcpy(current->op1, addr);
            }
        }
        current = current->next;
    }
    delete_list(label_head);
    // vai percorrer olhando o op1 e o op2 da linha pra checar se a variável foi definida como label
    // só chama se o op1/op2 não estiver vazio!
    // só chama se o op1/op2 não for número (atoi) (caso do EQU e de outras diretivas)!!
}


/*CHECK IF LABEL WAS DEFINED*/
int is_label_in_list(char* label, node_t* head) {
    node_t *current = head->next;

    while(current != NULL) {
        /*FOUND LABEL DEFINITION -> RETURN ITS ADDRS*/
        if(strcmp(current->label, label) == 0) {
            return current->address;
        }
        current = current->next;
    }
    return -1;
}

node_t* make_label_addr_list(node_t* label_head, node_t* head) {
    node_t *current = head->next;

    while(current != NULL) {
        /*FOUND LABEL IN CODE*/
        if(current->label[0] != '\0') {
            label_head = add_line(label_head, current->label, current->opcode, current->op1, current->op2, current->count, current->address, current->lexic_flag, current->syntatic_flag);
        }
        current = current->next;
    }
    return label_head;
}

int is_numeric (const char *s) {
    char * p;
    if (s == NULL || *s == '\0' || isspace(*s)) {
        return 0;
    }
    strtod (s, &p);
    return *p == '\0';
}
