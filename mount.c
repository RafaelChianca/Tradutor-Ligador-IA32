#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "mount.h"


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

    temp = strchr(filename, '.');
    *temp = '\0';
    strcat(filename, ".pre.txt");

    fp = fopen (filename, "w");
    pre_processed = fopen("pre_processed.txt", "w");

    while(current != NULL) {
        directive_flag = in_vector (current->opcode, directives, 7);
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

        if (fp != NULL) {
            if (line[1][0] != '\0') {
                if (fp != NULL) {
                    fprintf(pre_processed, "%d\t", count);
                }
                for (i = 0; i < 5; i++) {
                    fprintf(fp, "%s\t", line[i]);
                    if (fp != NULL) {
                        if (line[i][0] == '\0') {
                            fprintf(pre_processed, "00\t");
                        }
                        else {
                            fprintf(pre_processed, "%s\t", line[i]);
                        }
                    }

                }
                    fprintf(fp, "\n");
                    fprintf(pre_processed, "\n");

            }
        }
        count = 0;
        memset(current->label, 0, sizeof(current->label));
        memset(line, 0, sizeof(line[0][0]) * 5 * MAXCN);
        previous = current;
        current = current->next;
    }

    delete_list(label_head);

    fclose(fp);
    fclose(pre_processed);

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

bool is_numeric (const char *s) {
    char * p;
    if (s == NULL || *s == '\0' || isspace(*s)) {
        return 0;
    }
    strtod (s, &p);
    return *p == '\0';
}

int get_opcode (char *mneumonic) {
    char *opcode[] = {"ADD","SUB","MULT","DIV","JMP","JMPN","JMPP","JMPZ","COPY","LOAD","STORE","INPUT","OUTPUT","STOP"};
    int i;

    for (i = 0; i < 14; i++) {
        if (strcmp(opcode[i], mneumonic) == 0) {
            return i+1;
        }
    }

    return -1;

}

void write_in_file (int *semantic_errors, node_t *head, char *filename, int errors) {
    FILE *fp;
    node_t *current = head->next;
    char *temp, filename_buffer[MAXCN];
    int i, flag = 0;

    strcpy(filename_buffer, filename);
    temp = strchr(filename_buffer, '.');
    *temp = '\0';

    if (errors) {
        strcat(filename_buffer, "_errors.txt");
    }
    else {
        strcat(filename_buffer, ".obj.txt");
    }

    fp = fopen (filename_buffer, "w");

    if (fp != NULL) {
        while (current != NULL) {
            if (!errors) {
                fprintf(fp, "%s ", current->opcode);
                fprintf(fp, "%s ", current->op1);
                fprintf(fp, "%s ", current->op2);
                fprintf(fp, "%s ", current->op3);

            }
            else {
                fprintf(fp, "%d", current->count);
                fprintf(fp, "\t");
                fprintf(fp, "\n");
            }
            flag = 0;
            current = current->next;
        }
        fclose (fp);
    }
}
