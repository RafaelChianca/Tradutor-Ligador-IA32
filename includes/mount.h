#ifndef LIST_H_
  #define LIST_H_
  #include "list.h"
#endif

void mountProgram(char *);
int isLabelInFile(char*);
void makeLabelAddrFile();
int getOpcode (char *);
int bigToLittleEndian(int);
void writeFile (node_t*, char*);
void removeChar(char *, char);
int jumpsShortOrNearCode(char *, int, int *);
