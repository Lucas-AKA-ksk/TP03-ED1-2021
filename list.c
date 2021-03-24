#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list createList()
{
    list l = (list)malloc(sizeof(TList));
    if(l)
    {
        l->first = NULL;
        l->last = NULL;
        l->current = NULL;
        l->size = 0;
    }
    return l;
}

void endlist(list l)
{
    TLNode *p;
    while(l->first)
    {
        p = l->first;
        l->first = l->first->next;
        free(p);
    }
    free(l);
}

int insertAtHead(list l, TLElement e)
{
    TLNode *p;
    p=(TLNode*)malloc(sizeof(TLNode));

    if(!p)
        return 0;

    p->info = e;
    p->next = l->first;
    l->first = p;
    if(l->size == 0)
        l->last = p;
    l->size++;
    return 1;
}

int insertAtTail(list l, TLElement e)
{
    TLNode *p;
    
    if(emptyList(l))
        return insertAtHead(l,e);
    
    p=(TLNode*)malloc(sizeof(TLNode));

    if(!p)
        return 0;

    p->info = e;
    p->next = NULL;
    l->last->next = p;
    l->last = p;

    l->size++;
    return 1;
}

int searchList(list l, int row, int col)
{
    l->current = l->first;
    while (l->current!=NULL)
    {
        if(l->current->info.row == row && l->current->info.col == col)
            return 1;            
        l->current = l->current->next;
    }
    return 0;
}

int emptyList(list l){
   return l->first==NULL;
}