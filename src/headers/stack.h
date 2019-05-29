typedef struct {
    int right;
    int left;
} Item;

typedef struct Cell_str *Pointer;
 
typedef struct Cell_str {
    Item item;
    Pointer prox;
} Cell;
 
typedef struct {
    Pointer bottom, top;
    int size;
} Stack;
 
void MakeEmptyStack(Stack *S);
int IsEmpty(const Stack *S);
void Push(Item x, Stack *S);
int Pop(Stack *S, Item *item);
int StackSize(const Stack *S);