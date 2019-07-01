#ifndef COMMON_H_
  #define COMMON_H_
  #include <stdlib.h>
  #include <stdio.h>
  #include <string.h>
  #include <ctype.h>
#endif

#ifndef READ_H_
  #define READ_H_
  #include "read.h"
#endif

#ifndef ANALYZER_H_
  #define ANALYZER_H_
  #include "analyzer.h"
#endif

void readAsmFile (char *filename, node_t *head) {

    FILE *asm_file;
    int address_counter = 0, aux, line_error = 0;
    int i = 0, first_char_flag = 0, index = 1, line_counter = 0;
    int j = 0, label_flag = 0, comment_flag = 0, plus_flag = 0;
    char file_token;
    char line[5][MAXCN] = {{0}};
    char buffer[MAXCN] = {0}, backup_buffer[MAXCN] = {0};

    /* OPEN AND VALIDADE asm_file*/
    if ((asm_file = fopen(filename, "r")) == NULL) {
        ("Unable to open asm file.\n");
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

                syntaticAnalyzer(line, &address_counter);

                head = addLine(head, line[0], line[1], line[2], line[3], line[4], line_counter, "");

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

void read_input_output(node_t* ia_32_head, int* inputOutputFlags) {
    node_t* current = ia_32_head->next;
    FILE *fp, *ia_32_fp;
    char *line;
    char *token;
    char linebuffer[5][MAXCN] = {{0}};
    int i;
    size_t len = 0;

    ia_32_fp = fopen("ia_32.s.txt", "a");
    fputs("\n", ia_32_fp);

    for (i = 0; i < 10; i++) {
        if (inputOutputFlags[i] == 1) {
            switch (i) {
                case 0:
                    fp = fopen ("../inputOutputs/LeerInteiro.txt", "r");
                break;
                case 1:
                    fp = fopen ("../inputOutputs/EscreverInteiro.txt", "r");
                break;
                case 2:
                    fp = fopen ("../inputOutputs/LeerChar.txt", "r");
                break;
                case 3:
                    fp = fopen ("../inputOutputs/EscreverChar.txt", "r");
                break;
                case 4:
                    fp = fopen ("../inputOutputs/LerHexa.txt", "r");
                break;
                case 5:
                    fp = fopen ("../inputOutputs/EscreverHexa.txt", "r");
                break;
                case 6:
                    fp = fopen ("../inputOutputs/LeerString.txt", "r");
                break;
                case 7:
                    fp = fopen ("../inputOutputs/EscreverString.txt", "r");
                break;
                case 8:
                    fp = fopen ("../inputOutputs/EscreveEnter.txt", "r");
                break;
                case 9:
                    fp = fopen ("../inputOutputs/EscreverCharSemEnter.txt", "r");
                break;
            }

            if (fp != NULL && ia_32_fp != NULL) {
                while ((getline(&line, &len, fp)) != -1) {
                    token = strtok(line, ";");
                    if (strcmp(line, "\n") != 0 && strcmp(line, "nop\n") != 0) {
                        if(token != NULL) {
                            fprintf(ia_32_fp, "%s\n", token);
                        }
                    }
                    else if(strcmp(line, "nop\n") == 0) {
                        fprintf(ia_32_fp, "%s", token);

                    }
                }
            }

            fclose(fp);
        }
    }
    fclose(ia_32_fp);

}
