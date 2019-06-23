#ifndef LIST_H_
  #define LIST_H_
  #include "list.h"
#endif

void mountProgram (node_t *, char *);
int isLabelInList (char* , node_t*, int);
node_t* makeLabelAddrList (node_t* , node_t* );
int getOpcode (char *);
void writeFile (node_t*, char*);
