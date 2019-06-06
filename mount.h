void mount_program (node_t *, char *);
int is_label_in_list (char* , node_t*, int);
node_t* make_label_addr_list (node_t* , node_t* );
bool is_numeric (const char *);
int get_opcode (char *);
void write_in_file (int *, node_t*, char*, int);
