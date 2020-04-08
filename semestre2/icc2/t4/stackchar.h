typedef struct no {
    char ope;
    double num;
    struct no *next;
} No;

typedef struct {
    No *header;
} Stack;

void create_stack(Stack *s);
int push_stack(Stack *s, char x, double y);
int empty_stack(Stack s);
int pop_stack(Stack *s, char *x, double *y);
void print_stack(Stack s);
char stack_top(Stack s);
int free_stack(Stack *s);
int inverted_stack(Stack *s);
