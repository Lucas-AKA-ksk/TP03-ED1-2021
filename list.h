#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct
{
    int row ,col;
}TLElement;
 
typedef struct LNode
{
    TLElement info;
    struct LNode *next;
}TLNode;

typedef struct
{
    TLNode *first, *last, *current;
    int size;
}TList;

typedef TList *list;

list createList();

void endlist(list l);

int insertAtHead(list l, TLElement e);

int insertAtTail(list l, TLElement e);

int searchList(list l, int row, int col);

int emptyList(list l);

#endif //LIST_H_INCLUDED