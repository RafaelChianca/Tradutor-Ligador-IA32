#define MAXCN 51

typedef enum { FALSE, TRUE } bool;

typedef struct node {
    char label[51];
    char opcode[51];
    char op1[51];
    char op2[51];
    int count;
    int address;
    bool lexic_flag;
    bool syntatic_flag;
    bool semantic_flag;
    struct node * next;

}node_t;

void delete_list(node_t *);
void read_file (char *);
node_t* initialize_list(node_t *);
void print_list(node_t *);
node_t* add_line(node_t *, char *, char *, char *, char *, int, int, bool, bool);
