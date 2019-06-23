#define MAXCN 51

typedef enum { FALSE, TRUE } bool;

typedef struct node {
    char label[51];
    char opcode[51];
    char op1[51];
    char op2[51];
    char op3[51];
    int count;
    int address;
    struct node * next;

}node_t;

void delete_list (node_t *);
node_t* initialize_list (node_t *);
void print_list (node_t *);
node_t* add_line (node_t *, char *, char *, char *, char *, char *, int, int);
node_t* create_node(char * ,char *, char *, char *, char *, int , int);
node_t* delete_node (node_t*, int );
node_t* in_list (char *, node_t *);
node_t* add_next_node (node_t *, node_t *);
