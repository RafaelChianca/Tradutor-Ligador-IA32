// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #include "list.h"

#ifndef COMMON_H_
  #define COMMON_H_
  #include <stdlib.h>
  #include <stdio.h>
  #include <string.h>
#endif

#ifndef LIST_H_
  #define LIST_H_
  #include "list.h"
#endif

node_t* initializeList(node_t *head) {

    head = (node_t *)malloc(sizeof(node_t));

    if (head == NULL) {
        printf("Unable to create list.\n");
        exit(1);
    }

    head->count = 0;
    head->address = 0;
    head->next = NULL;

    return head;
}

node_t* createNode(char *label ,char *opcode, char *op1, char *op2, char *op3, int count, int address){
    node_t* node = (node_t *)malloc(sizeof(node_t));
    strcpy(node->label, label);
    strcpy(node->opcode, opcode);
    strcpy(node->op1, op1);
    strcpy(node->op2, op2);
    strcpy(node->op3, op3);
    node->count = count;
    node->address = address;

    node->next = NULL;
    return node;
}

void printList(node_t *head) {

    node_t *current = head->next;
        printf("\nLine\tLabel\tOpcode\tOp1\tOp2\tOp3\n");
        while (current != NULL) {
            printf("%d\t", current->count);
            printf("%d\t", current->address);
            printf("%s\t", current->label);
            printf("%s\t", current->opcode);
            printf("%s\t", current->op1);
            printf("%s\t", current->op2);
            printf("%s\t", current->op3);
            current = current->next;
        }

}

node_t* addLine(node_t *head, char *label ,char *opcode, char *op1, char *op2, char *op3, int count, int address) {
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (node_t *)malloc(sizeof(node_t));
    strcpy(current->next->label, label);
    strcpy(current->next->opcode, opcode);
    strcpy(current->next->op1, op1);
    strcpy(current->next->op2, op2);
    strcpy(current->next->op3, op3);
    current->next->count = count;
    current->next->address = address;

    current->next->next = NULL;

    return head;
}


node_t* deleteNode(node_t* head, int line) {
    node_t * current = head->next;
    node_t * previous = head;

    while (current->count != line) {
        previous = current;
        current = current->next;
    }

    previous->next = current->next;
    free(current);
    memset(current->label, 0, sizeof(current->label));
    current = previous;

    return current;

}

void deleteList(node_t * head)  {
    node_t* current = head;
    node_t* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

node_t* inList(char *needle, node_t *haystack) {
    node_t* current = haystack->next;
    while (current != NULL) {
        if (strcmp(current->label, needle) != 0) {
            current = current->next;
        } else {
            break;
        }
    }
    return current;

}

node_t* addNextNode(node_t *prev_position, node_t *node) {
    node_t *temp;

    temp = prev_position->next;
    prev_position->next = node;
    node->next = temp;

    return node;
}
