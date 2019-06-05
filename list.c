#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"


node_t* initialize_list(node_t *head) {

    head = (node_t *)malloc(sizeof(node_t));

    if (head == NULL) {
        printf("Unable to create list.\n");
        exit(1);
    }

    head->count = 0;
    head->address = 0;
    head->lexic_flag = 0;
    head->syntatic_flag = 0;
    head->semantic_flag = 0;
    head->next = NULL;

    return head;
}

void print_list(node_t *head) {

    node_t *current = head->next;
        printf("\nLine\tAddr\tLabel\tOpcode\tOp1\tOp2\tLexic\tSyntatic\n");
        while (current != NULL) {
            printf("%d\t", current->count);
            printf("%d\t", current->address);
            printf("%s\t", current->label);
            printf("%s\t", current->opcode);
            printf("%s\t", current->op1);
            printf("%s\t", current->op2);
            printf("%d\t", current->lexic_flag);
            printf("%d\n", current->syntatic_flag);
            current = current->next;
        }

}

node_t* add_line(node_t *head, char *label ,char *opcode, char *op1, char *op2, int count, int address, bool lexic, bool syntatic) {
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (node_t *)malloc(sizeof(node_t));
    strcpy(current->next->label, label);
    strcpy(current->next->opcode, opcode);
    strcpy(current->next->op1, op1);
    strcpy(current->next->op2, op2);
    current->next->count = count;
    current->next->address = address;
    current->next->lexic_flag = lexic;
    current->next->syntatic_flag = syntatic;

    current->next->next = NULL;

    return head;
}

void delete_list(node_t * head)  {
    node_t* current = head;
    node_t* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
