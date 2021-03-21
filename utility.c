#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

/* Substitui o newline(\n) por nul(\0) */
void newline_remover(char *s)
{
    if(s[strlen(s)-1]=='\n')
        s[strlen(s)-1]='\0';
}

/* Verifica a existencia de um newline em uma string 's',
caso não exista, consome o buffer, caso exista, chama newline_remover */
void check_newline(char *s)
{
    if(strchr(s,'\n')==NULL) /* Se \n  não for encontrado*/
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    else 
        newline_remover(s);
}