#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.c"
#include "analyzer.c"
#include "mount.c"
#include "macro.c"
#include "read.c"

int main(int argc, char *argv[]) {

    node_t *head;

    head = initialize_list(head);
    read_file(argv[1], head);
    mount_program(head, argv[1]);
    write_in_file(head, argv[1]);
    delete_list(head);

    return 0;
}
