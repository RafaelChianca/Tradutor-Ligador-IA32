#define MAXCN 51

typedef enum { FALSE, TRUE } bool;

typedef struct node {
    char label[51];
    char opcode[51];
    char op1[51];
    char op2[51];
    char op3[51];
    int count;
    char address[15];
    struct node * next;

}node_t;

void deleteList (node_t *);
node_t* initializeList (node_t *);
void printList (node_t *);
node_t* addLine (node_t *, char *, char *, char *, char *, char *, int, char *);
node_t* createNode(char * ,char *, char *, char *, char *, int , char *);
node_t* deleteNode (node_t*, int );
node_t* inList (char *, node_t *);
node_t* addNextNode (node_t *, node_t *);
void lineToList(char*, char[][MAXCN]);
