#ifndef COMMON_H_
  #define COMMON_H_
  #include <stdlib.h>
  #include <stdio.h>
  #include <string.h>
#endif

#ifndef MOUNT_H_
  #define MOUNT_H_
  #include "mount.h"
#endif

#ifndef ANALYZER_H_
  #define ANALYZER_H_
  #include "analyzer.h"
#endif


void mount_program(node_t *head, char *filename) {
    node_t *label_head;
    char *directives[] = {"SECTION", "CONST", "EQU", "IF", "MACRO", "END", "SPACE"};
    char addr[MAXCN], opcode_buffer[MAXCN], buffer[MAXCN];
    char line[5][MAXCN] = {{0}};
    node_t *current = head->next, *previous = head;
    int spaces = 0, i, count;
    int label_flag = 0, opcode_value = 0, directive_flag = 0, op2_flag = 0;
    FILE *fp, *pre_processed;
    char *temp;

    label_head = initialize_list(label_head);
    label_head = make_label_addr_list(label_head, head);

    while(current != NULL) {
        directive_flag = inVector(current->opcode, directives, 7);
        strcpy(line[0], current->label);

        /*IT'S NOT EMPTY AND IT'S NOT A DIRECTIVE*/
        if (current->op1 && !directive_flag) {
            label_flag = is_label_in_list(current->op1, label_head, 0);

            count = current->count;

            /*CASE COPY*/
            if (current->op2) {
                op2_flag = is_label_in_list(current->op2, label_head, 0);
                if (op2_flag != -1) {
                    strcpy(line[2], current->op1);
                    strcpy(line[3], current->op2);
                    memset(current->op2, 0, sizeof(current->op2));
                    /*TURN THE ADDRESS NUMBER INTO A STRING*/
                    sprintf(addr, "%d", op2_flag);
                    strcpy(current->op2, addr);
                }
            }

            if (label_flag != -1) {
                /*TURN THE ADDRESS NUMBER INTO A STRING*/
                sprintf(addr, "%d", label_flag);
                strcpy(line[2], current->op1);
                strcpy(line[3], current->op2);
                memset(current->op1, 0, sizeof(current->op1));
                strcpy(current->op1, addr);
            }
            opcode_value = get_opcode(current->opcode);
            // TRADES OPCODE FOR ITS VALUE
            if (opcode_value != -1) {
                strcpy(line[0], current->label);
                strcpy(line[1], current->opcode);
                memset(current->opcode, 0, sizeof(current->opcode));
                /*TURN THE OPCODE VALUE INTO A STRING*/
                sprintf(opcode_buffer, "%d", opcode_value);
                strcpy(current->opcode, opcode_buffer);
            }
        }
        /*CASE SPACE*/
        else if (strcmp(current->opcode, "SPACE") == 0) {
            spaces = atoi(current->op1);
            count = current->count;
            strcpy(line[1], current->opcode);
            strcpy(line[2], current->op1);
            strcpy(line[3], current->op2);
            memset(current->op1, 0, sizeof(current->op1));
            strcpy(current->opcode, "00");

            for (i = 1; i < spaces; i++) {
                strcat(current->opcode, "\n\n");
                sprintf(buffer, "%d", current->address+i);
                strcat(current->opcode, buffer);
                strcat(current->opcode, "\t00");
            }
        }

        /*CASE END*/
        else if (strcmp(current->opcode, "END") == 0) {
            count = current->count;
            current = delete_node(head, current->count);
        }
        else if (current->op1 && directive_flag) {
            /* CASE IF */
            count = current->count;
            if (strcmp(current->opcode, "IF") == 0) {
                label_flag = is_label_in_list(current->op1, label_head, 1);
                /* DELETE IF LINE*/
                current = delete_node(head, current->count);
                if (label_flag == 0) {
                    /* DELETE NEXT LINE */
                    current = delete_node(head, current->next->count);
                }
            }
            /*CASE CONST*/
            else if (strcmp(current->opcode, "CONST") == 0) {
                count = current->count;
                strcpy(line[1], current->opcode);
                strcpy(line[2], current->op1);
                strcpy(line[3], current->op2);
                memset(current->opcode, 0, sizeof(current->opcode));
                strcpy(current->opcode, current->op1);
                memset(current->op1, 0, sizeof(current->op1));
            }
            /*CASE EQU AND SECTION*/
            else if (strcmp(current->opcode, "EQU") == 0) {
                count = current->count;
                current = delete_node(head, current->count);
            }
            else if (strcmp(current->opcode, "SECTION") == 0) {
                strcpy(line[0], current->opcode);
                strcpy(line[1], current->op1);
                strcpy(line[2], current->op2);
                count = current->count;
                current = delete_node(head, current->count);
            }
        }

        count = 0;
        memset(current->label, 0, sizeof(current->label));
        memset(line, 0, sizeof(line[0][0]) * 5 * MAXCN);
        previous = current;
        current = current->next;
    }

    delete_list(label_head);

}


/*CHECK IF LABEL WAS DEFINED*/
int is_label_in_list(char* label, node_t* head, int case_if) {
    node_t *current = head->next;
    while(current != NULL) {
        /*FOUND LABEL DEFINITION -> RETURN ITS ADDRS*/
        if(strcmp(current->label, label) == 0) {
            if(!case_if) {
                return current->address;
            }
            else {
                return atoi(current->op1);
            }
        }
        current = current->next;
    }
    return -1;
}

node_t* make_label_addr_list(node_t* label_head, node_t* head) {
    node_t *current = head->next;

    while(current != NULL) {
        /*FOUND LABEL IN CODE*/
        if(current->label[0] != '\0' && strcmp(current->label, "00") != 0) {
            label_head = add_line(label_head, current->label, current->opcode, current->op1, current->op2, current->op3, current->count, current->address);
        }
        current = current->next;
    }
    return label_head;
}

int get_opcode (char *mneumonic) {
    char *opcode[] = {"ADD","SUB","MULT","DIV","JMP","JMPN","JMPP","JMPZ","COPY","LOAD","STORE","INPUT","OUTPUT","STOP","C_INPUT","C_OUTPUT","H_INPUT","H_OUTPUT","S_INPUT","S_OUTPUT"};
    int i;

    for (i = 0; i < 20; i++) {
        if (strcmp(opcode[i], mneumonic) == 0) {
            return i+1;
        }
    }

    return -1;

}

void writeFile (node_t *head, char *filename) {
    FILE *fp;
    node_t *current = head->next;
    char *temp, filename_buffer[MAXCN];
    int i;

    strcpy(filename_buffer, filename);

    strcat(filename_buffer, ".s.txt");

    fp = fopen (filename_buffer, "w");

    if (fp != NULL) {
        while (current != NULL) {
            if(strcmp(current->label, "") != 0) {
                fprintf(fp, "%s:\t", current->label);
            }
            else {
                fprintf(fp, "\t");
            }
            fprintf(fp, "%s\t", current->opcode);
            fprintf(fp, "%s\t", current->op1);
            fprintf(fp, "%s\t", current->op2);
            fprintf(fp, "%s\t", current->op3);
            fprintf(fp, "\n");

            current = current->next;
        }
        fclose (fp);
    }
}