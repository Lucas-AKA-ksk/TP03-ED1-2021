#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef struct
{
    int path_row, path_col;
}TSElement;

typedef struct SNode
{
    TSElement info;
    struct SNode *next;
}TSNode;
typedef struct
{
    TSNode *top, *current;
    int size;
}TStack;

typedef TStack *stack;

stack createStack();

void endStack(stack s);

int push(stack s, TSElement e);

int pop(stack s, TSElement *e);

void insertAtBottom(stack s,TSElement e);

void reverseStack(stack s);

int searchStack(stack s, int row, int col);

int isEmpty(stack s);

#endif //STACK_H_INCLUDED