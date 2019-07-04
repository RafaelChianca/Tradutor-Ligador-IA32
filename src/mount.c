#ifndef COMMON_H_
  #define COMMON_H_
  #include <stdlib.h>
  #include <stdio.h>
  #include <string.h>
  #include <math.h>
#endif

#ifndef MOUNT_H_
  #define MOUNT_H_
  #include "mount.h"
  #include "convert.h"

#endif

#ifndef ANALYZER_H_
  #define ANALYZER_H_
  #include "analyzer.h"
#endif


void mountProgram(node_t *head, char *filename) {
    FILE *fp, *fp_obj, *fp_nop;
    node_t *current = head->next;
    char *temp, filename_buffer[MAXCN], *instruction, instruction_aux[100], label_aux[100];
    char addr[10], aux[2];
    int addr_count = -14, text_flag = 0, addr_label, offset, jump_offset = 0;
    int nops = 0, i, label_flag = 0;
    char *line;
    size_t len = 0;
    char *io_functions[] = {"EscreveEnter","EscreverChar", "EscreverCharSemEnter", "EscreverHexa", "EscreverInteiro", "EscreverString", "LeerChar", "LeerInteiro", "LeerString", "LerHexa"};
    strcpy(filename_buffer, filename);

    temp = strchr(filename_buffer, '.');
    *temp = '\0';

    strcat(filename_buffer, ".o");

    fp = fopen("aux.s", "r");
    fp_obj = fopen(filename_buffer, "w");
    fp_nop = fopen("aux2.s", "w");

    if(fp != NULL && fp_obj != NULL) {
        while ((getline(&line, &len, fp)) != -1) {
            fputs(line, fp_nop);
            if(strstr(line, ".text")){
                text_flag = 1;
            }
            if(text_flag == 1) {
                if(!strstr(line, "nop") && strcmp(line, "\n") != 0 && !strstr(line, "_start")) {
                    // if(strchr(line, ':') && label_flag == 0){
                    //     strcpy(label_aux, line);
                    //     strtok(label_aux, ":");
                    //     if (inArray(label_aux, io_functions) != -1) {
                    //         label_flag = 1;
                    //     }
                    // }
                    addr_count+=7;
                    jump_offset = jumpsShortOrNearCode(line, 0x08048080 + addr_count + 6, &nops);
                    if(jump_offset != -2 && label_flag != 0) {
                        for (i = 0; i < nops; i++) {
                            fputs("nop\n", fp_nop);
                        }
                    }
                    if(jump_offset == -2 || jump_offset == -1) {
                        strcpy(instruction_aux, line);
                        strtok(instruction_aux, ";");
                        instruction = strtok(NULL, ";");
                        if(instruction == NULL) {
                            continue;
                        }
                        strcpy(instruction_aux, instruction);
                    }

                    addr_label = isLabelInFile(line);
                    if(addr_label != -1) {
                        if(jump_offset != -2 && jump_offset != -1) {
                            offset = 0x08048080 + addr_count + 2;
                        }
                        else {
                            if(strstr(line, "call")) {
                                offset = 0x08048080 + addr_count + 5;
                                if(!strstr(instruction, "e8")) {
                                    strcpy(instruction_aux, "e8\n");
                                }

                            }
                            else
                                offset = 0x08048080 + addr_count + 6;
                        }
                        offset = addr_label - offset;
                        printf("1-%x\n", offset);
                        printf("%s\n", line);
                        if(offset > 0xf || offset < 0x0) {
                            offset = bigToLittleEndian(offset);
                        }
                        sprintf(addr, "%x", offset);
                        temp = strchr(instruction_aux, '\n');
                        *temp = '\0';
                        if (jump_offset != -2 && jump_offset != -1) {
                            printf("2-%x\n", offset);
                            getchar();
                            if (offset < 0xf) {
                                addr[2] = '\0'; // only the first byte in little endian
                                strcpy(aux, "0");
                                strcat(aux, addr);
                                strcpy(addr, aux);
                                if(strlen(addr) == 3) {
                                    sprintf(addr, "%x", offset);
                                    addr[2] = '\0';
                                }
                            }
                            sprintf(instruction_aux, "%x", jump_offset);

                            strcat(instruction_aux, addr);
                        } else {
                            strcat(instruction_aux, addr);
                        }
                    }
                    if(instruction_aux != NULL && strcmp(instruction_aux, "\n") != 0 && label_flag == 0) {
                        fprintf(fp_obj, "%s\n", instruction_aux);
                    }
                }
            }
        }
    }

    fclose(fp);
    fclose(fp_obj);
    fclose(fp_nop);

}

int bigToLittleEndian(int little_endian) {
    return (((little_endian & 0x000000FF) << 24) |
            ((little_endian & 0x0000FF00) <<  8) |
            ((little_endian & 0x00FF0000) >>  8) |
            ((little_endian & 0xFF000000) >> 24));
}


/*Check if label was defined and returns its address*/
int isLabelInFile(char* instruction) {
    FILE *fp;
    int integer;
    char *line, *label, *addr, aux[100];
    size_t len = 0;
    fp = fopen("labels.txt", "r");

    removeChar(instruction, '[');
    removeChar(instruction, ']');

    if(fp != NULL) {
        while ((getline(&line, &len, fp)) != -1) {
            label = strtok(line, ";");
            strcpy(aux, label);
            addr = strtok(NULL, ";");
            strcat(aux, "\t;");
            if(strstr(instruction, aux)) {
                integer = (int)strtol(addr, NULL, 16);
                return integer;
            }
        }
        return -1;
    }
}

int jumpsShortOrNearCode(char *instruction, int addr_count, int* nops) {
    int offset;

    if (strstr(instruction, "jl")) {
        offset = isLabelInFile(instruction);
        offset = fabs(offset - addr_count);
        if(!(offset >= -128 && offset < 127)) {
            *nops = 1;
            return -1;
        }
        else {
            *nops = 5;
            return 0x7c;
        }
    }else if (strstr(instruction, "jg")) {
        offset = isLabelInFile(instruction);
        offset = fabs(offset - addr_count);
        if(!(offset >= -128 && offset < 127)) {
            *nops = 1;
            return -1;
        }
        else {
            *nops = 5;
            return 0x7f;
        }
    }else if (strstr(instruction, "je")) {
        offset = isLabelInFile(instruction);
        offset = fabs(offset - addr_count);
        if(!(offset >= -128 && offset < 127)) {
            *nops = 1;
            return -1;
        }
        else {
            *nops = 5;
            return 0x74;
        }
    }else if (strstr(instruction, "jne")) {
        *nops = 0;
        return 0x75;
    }else if (strstr(instruction, "jbe")) {
        *nops = 0;
        return 0x76;
    }else if (strstr(instruction, "jb")) {
        *nops = 0;
        return 0x72;
    }else if (strstr(instruction, "jmp")) {
        *nops = 0;
        return 0xeb;
    }else if (strstr(instruction, "loop")) {
        *nops = 0;
        return 0xe2;
    }
    *nops = 0;
    return -2;
}

void removeChar(char *s, char c){
    int i, j, n = strlen(s);
        for (i=j=0; i<n; i++){
            if (s[i] != c) {
                s[j++] = s[i];
            }
        }
    s[j] = '\0';
}

void makeLabelAddrFile() {
    FILE *fp_ia_32, *fp_label_addr;
    char *temp, filename_buffer[MAXCN];
    char *line;
    char *token, count[MAXCN];
    int i, line_count = 0;
    int text_initial_addr = 0x08048080;
    size_t len = 0;

    fp_ia_32 = fopen ("aux.s", "r");

    fp_label_addr = fopen("labels.txt", "w");

    if (fp_ia_32 != NULL && fp_label_addr != NULL) {
        while ((getline(&line, &len, fp_ia_32)) != -1) {
            if(!strstr(line, "nop") && !strstr(line, "_start") && strcmp(line, "\n") != 0) {
                line_count+=7;
                if(strstr(line, ".text")){
                    line_count = 0x08048079;

                } else if(strstr(line, ".data")) {
                    line_count = -7;
                }
            }
            token = strchr(line, ':');
            if (strcmp(line, "\n") != 0) {
                if (token != NULL) {
                    token = strtok(line, ":");
                    sprintf(count, "%x", line_count);
                    strcat(token, ";");
                    strcat(token, count);
                    strcat(token, "\n");
                    fputs(token, fp_label_addr);
                }
            }
        }
    }
    fclose(fp_ia_32);
    fclose(fp_label_addr);
}


void writeFile (node_t *head, char *filename) {
    FILE *fp_aux, *fp_org;
    node_t *current = head->next;
    char *temp, filename_buffer[MAXCN];
    int i;

    strcpy(filename_buffer, filename);

    temp = strchr(filename_buffer, '.');
    *temp = '\0';

    strcat(filename_buffer, ".s");

    /*won't contain nops, only the translation.*/
    fp_org = fopen(filename_buffer, "w");

    /*will contain nops in order to help count labels. Will be deleted afterwards.*/
    fp_aux = fopen("aux.s", "w");

    if (fp_org != NULL && fp_aux != NULL) {
        while (current != NULL) {
            if(strcmp(current->label, "") != 0) {
                fprintf(fp_org, "%s:\t", current->label);
                fprintf(fp_aux, "%s:\t", current->label);
            }
            else {
                fprintf(fp_org, "\t");
                fprintf(fp_aux, "\t");
            }
            fprintf(fp_org, "%s\t", current->opcode);
            fprintf(fp_aux, "%s\t", current->opcode);
            if(strcmp(current->op2, "") != 0) {
                fprintf(fp_org, "%s,\t", current->op1);
                fprintf(fp_aux, "%s,\t", current->op1);
            }
            else {
                fprintf(fp_org, "%s\t", current->op1);
                fprintf(fp_aux, "%s", current->op1);
            }
            fprintf(fp_org, "%s", current->op2);
            fprintf(fp_aux, "%s", current->op2);
            fprintf(fp_org, "\n");
            fprintf(fp_aux, "\t;%s", current->address);
            fprintf(fp_aux, "\n");
            for (i = 0; i < current->count; i++) {
                fprintf(fp_aux, "nop\n");
            }
            current = current->next;
        }
        fclose (fp_org);
        fclose (fp_aux);
    }
}
