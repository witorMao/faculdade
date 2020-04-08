typedef struct notree {
    char oper;
    double number;
    struct notree *parent, *right, *left;
} Notree;

typedef struct {
    Notree *root;
}Tree;

Notree* create_root(char x, double y);
int empty_tree(Notree *root);
Notree* add_child(Notree *parent, char x, double y);
void print_tree(Notree *root, int counter);
void free_tree(Notree *root);
