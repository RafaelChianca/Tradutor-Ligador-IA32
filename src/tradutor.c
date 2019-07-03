#ifndef COMMON_H_
  #define COMMON_H_
  #include <stdlib.h>
  #include <stdio.h>
  #include <string.h>
#endif

#ifndef LIST_H_
  #define LIST_H_
  #include "list.h"
#endif

#ifndef READ_H_
  #define READ_H_
  #include "read.h"
#endif

#ifndef MOUNT_H_
  #define MOUNT_H_
  #include "mount.h"
#endif

#ifndef CONVERT_H_
  #define CONVERT_H_
  #include "convert.h"
#endif

int main(int argc, char *argv[]) {

    node_t *head, *ia_32_head;
    int inputOutputsFlags[10] = {0};

    head = initializeList(head);
    ia_32_head = initializeList(ia_32_head);

    readAsmFile(argv[1], head);
    ia_32_head = translate(head, ia_32_head, inputOutputsFlags);
    writeFile(ia_32_head, argv[1]);

    deleteList(head);

    readInputOutput(ia_32_head, inputOutputsFlags, argv[1]);
    makeLabelAddrFile();
    mountProgram(ia_32_head, argv[1]);

    remove("aux.s");
    deleteList(ia_32_head);

    return 0;
}
