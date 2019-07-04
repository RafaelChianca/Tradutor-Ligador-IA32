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

    mountProgram(argv[1]);

    remove("aux.s");
    remove("aux2.s");
    remove("labels.txt");
    return 0;
}
