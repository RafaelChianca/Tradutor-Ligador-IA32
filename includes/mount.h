#ifndef LIST_H_
  #define LIST_H_
  #include "list.h"
#endif

void mountProgram (node_t *, char *);
int isLabelInList (char* , node_t*, int);
void makeLabelAddrFile();
int getOpcode (char *);
void writeFile (node_t*, char*);
