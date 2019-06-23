#ifndef LIST_H_
  #define LIST_H_
  #include "list.h"
#endif

void mount_program (node_t *, char *);
int is_label_in_list (char* , node_t*, int);
node_t* make_label_addr_list (node_t* , node_t* );
int get_opcode (char *);
void writeFile (node_t*, char*);
