#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "read.h"

void read_file (char *filename, node_t *head) {

    FILE *asm_file;
    int address_counter = 0, aux, line_error = 0;
    int i = 0, first_char_flag = 0, index = 1, line_counter = 0;
    int j = 0, label_flag = 0, comment_flag = 0, plus_flag = 0;
    char file_token;
    char line[5][MAXCN] = {{0}};
    char buffer[MAXCN] = {0}, backup_buffer[MAXCN] = {0};

    /* OPEN AND VALIDADE asm_file*/
    if ((asm_file = fopen(filename, "r")) == NULL) {
        printf("Unable to open asm file.\n");
        exit(0);
    }

    /* READ FROM asm_file */
    while (file_token != EOF) {
        while (( (file_token = fgetc(asm_file)) != ' ' && file_token != '\t' && file_token != '\n' && file_token != EOF)) {
            /*valid char found (not TAB or ENTER)*/
            first_char_flag = 1;
            /*Comment section found*/
            if (file_token == ';') {
                comment_flag = 1;
            }
            if (!comment_flag) {
                /*Label call found*/
                if (file_token == ':') {
                    label_flag = 1;
                }
                /*Second operand found*/
                else if (file_token == ',') {
                    continue;
                }
                /*Sum operation found*/
                else if (file_token == '+' || plus_flag) {
                    plus_flag = 1;
                    /*saves whatever comes after the + sign in backup_buffer*/
                    backup_buffer[j++] = toupper(file_token);
                }
                else {
                    buffer[i++] = toupper(file_token);
                }
            }
        }
        buffer[i] = '\0';
        backup_buffer[j] = '\0';
        i = 0;
        /*moves buffer to line according to index (wheter is a label, opcode or operator)*/
        if ((file_token == ' ' || file_token == '\t') && !comment_flag && first_char_flag) {
            if(label_flag) {
                index = 0;
            }
            if(!plus_flag) {
                /* SAVE BUFFER TO LINE */
                strcpy(line[index], buffer);
                index++;
                /* FREE BUFFER */
                memset(buffer, 0, sizeof(buffer));
            }
            first_char_flag = 0;
        }
        else if (file_token == '\n') {
            line_counter++;
            if (first_char_flag) {
                if (label_flag) {
                    index = 0;
                }
                if (plus_flag) {
                    strcat(line[index - 1], backup_buffer);
                    plus_flag = 0;
                    j = 0;
                }
                else {
                    strcpy(line[index], buffer);
                }
                index++;
                first_char_flag = 0;
                memset(buffer, 0, sizeof(buffer));
                memset(backup_buffer, 0, sizeof(backup_buffer));
            }
            if (!comment_flag && index >= 2) {
                aux = address_counter;

                syntatic_analyzer(line, &address_counter);

                head = add_line(head, line[0], line[1], line[2], line[3], line[4], line_counter, aux);

                memset(line, 0, sizeof(line[0][0]) * 5 * MAXCN);
                index = 1;
            } else {
                comment_flag = 0;
            }
            line_error = 0;
        }
        label_flag = 0;
    }
    fclose(asm_file);
}
