#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.c"
#include "analyzer.c"
#include "mount.c"


int main(int argc, char *argv[]) {

    read_file(argv[1]);

    return 0;
}

void read_file (char *filename) {

    FILE *asm_file;
    node_t *head;
    int address_counter = 0, syntatic_errors = 0, lexic_errors = 0, aux;
    int i = 0, first_char_flag = 0, second_op_flag = 0, index = 1, line_counter = 0;
    int j = 0, label_flag = 0, comment_flag = 0, copy_flag = 0, space_flag = 0, plus_flag = 0;
    char file_token;
    char line[4][MAXCN] = {{0}};
    char buffer[MAXCN] = {0}, backup_buffer[MAXCN] = {0};

    /* OPEN AND VALIDADE asm_file*/
    if ((asm_file = fopen(filename, "r")) == NULL) {
        printf("Unable to open asm file.\n");
        exit(0);
    }

    head = initialize_list(head);

    /* READ FROM asm_file */
    while (file_token != EOF) {
        while (( (file_token = fgetc(asm_file)) != ' ' && file_token != '\t' && file_token != '\n' && file_token != EOF)) {
            first_char_flag = 1;
            if (file_token == ';') {
                comment_flag = 1;
            }
            if (!comment_flag) {
                if (file_token == ':') {
                    label_flag = 1;
                }
                else if (file_token == ',') {
                    second_op_flag = 1;
                }
                else if (file_token == '+' || plus_flag) {
                    plus_flag = 1;
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
                lexic_errors = lexic_analyzer(line);
                aux = address_counter;
                syntatic_errors = syntatic_analyzer(line, &address_counter);
                head = add_line(head, line[0], line[1], line[2], line[3], line_counter, aux, lexic_errors, syntatic_errors);

                /* FREE LINE */
                memset(line, 0, sizeof(line[0][0]) * 4 * MAXCN);
                index = 1;
            } else {
                comment_flag = 0;
            }

        }
        label_flag = 0;
    }
    print_list(head);
    mount_program(head);
    print_list(head);
    printf("\n");
    delete_list(head);
    fclose(asm_file);
}
