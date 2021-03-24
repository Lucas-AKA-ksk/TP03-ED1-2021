#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/* Cria uma pilha alocando espaço para a mesma e
 caso consiga alocar, inicializa os valores s->top e s->size
 e retorna a pilha */
stack createStack()
{
    stack s =(stack)malloc(sizeof(TStack));
   	if(s)
    {
      	s->top = NULL;
      	s->size = 0;
   	}
   	return s;
}

/* Percorre os nodos da pilha liberando os
 espaços que foram alocados para os mesmos,
 em seguida libera o espaço alocado para a pilha */
void endStack(stack s)
{
   	TSNode *a;
   	while(s->top!=NULL)
    {
      	a = s->top;
      	s->top = s->top->next;
      	free(a);
   	}
   	free(s);
}

/* Insere um elemento 'e' na pilha */
int push(stack s, TSElement e)
{
    TSNode *a;
   	a=(TSNode*)malloc(sizeof(TSNode));
   	if(!a)
      	return 0;

   	else
	{
    	a->info =e;
    	a->next=s->top;
    	s->top = a;
    	s->size++;
    	return 1;
	}
}

/* Remove um elemento da pilha, guardando o valor do mesmo em 'e' */
int pop(stack s, TSElement *e)
{
    TSNode *a;

   	if(!s->top)
     	return 0;

   	a=s->top;
   	s->top = s->top->next;
   	*e = a->info;
   	free(a);
   	s->size--;
   	return 1;
}

/* Função recursiva para inserir um item no fundo de uma pilha */
void insertAtBottom(stack s,TSElement e)
{
	TSElement temp;
    if (isEmpty(s))
        push(s, e);
    else
    {
        /* Segura todos os itens na Pilha de execução
         até que chege ao final da pilha 's'
         quando 's' estiver vazia, a condição
         isEmpty(s) acima será verdadeira
         e o elemento 'e' será inserido no fundo da pilha */ 
        pop(s,&temp);
        insertAtBottom(s, e);
  
        /* Quando o item 'e' for inserido no fundo 
         da pilha, insere o proximo item na pilha de execução */
        push(s,temp);
    }
}

/* Função recursiva para inverter a ordem dos elementos de uma pilha */
void reverseStack(stack s)
{
	TSElement e;
    if (!isEmpty(s))
    {
        // Segura todos os itens na pilha de execução 
        // Até que chegue ao final da pilha 's' */
        // reach end of the stack 
        pop(s,&e);
        reverseStack(s);

		/* insere todos os itens na pilha de execução
		 um por um de volta na pilha 's',
		 sendo inseridos um a um no fundo da pilha 's' */ 
        insertAtBottom(s,e);
    }
}

/* Função que busca pela existencia de uma informação
 na pilha, neste caso um combinação de linha/coluna */
int searchStack(stack s, int row, int col)
{
    s->current = s->top;
    while (s->current!=NULL)
    {
        if(s->current->info.path_row == row && s->current->info.path_col == col)
            return 1;
            
        s->current = s->current->next;
    }
    return 0;
}

/* Verifica se uma pilha está vazia ou não */
int isEmpty(stack s)
{
    return s->top == NULL;
}