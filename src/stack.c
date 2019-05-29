#include "headers/stack.h"
//#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
 
void MakeEmptyStack(Stack *S) {
    S->top = (Pointer) malloc(sizeof(Cell));
    S->bottom = S->top;
    S->top->prox = NULL;
    S->size = 0;
}
 
int IsEmpty(const Stack *S) {
    return (S->top == S->bottom);
}
 
void Push(Item x, Stack *S) {
    Pointer aux;
    aux = (Pointer) malloc(sizeof(Cell));
    S->top->item = x;
    aux->prox = S->top;
    S->top = aux;
    S->size++;
}
 
int Pop(Stack *S, Item *item) {
    Pointer q;
    if (IsEmpty(S)) {
        printf("Error: empty stack\n");
        return 0;
    }
    q = S->top;
    S->top = q->prox;
    free(q);
    S->size--;
    *item = S->top->item;
    return 1;
}
 
int StackSize(const Stack *S) {
    return (S->size);
}