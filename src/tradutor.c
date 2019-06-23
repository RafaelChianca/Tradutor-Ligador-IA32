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

    head = initialize_list(head);
    readFile(argv[1], head);
    writeFile(head, argv[1]);
    ia_32_head = translate(head);
    delete_list(ia_32_head);
    delete_list(head);

    return 0;
}