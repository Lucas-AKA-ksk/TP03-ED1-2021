#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"
#include "utility.h"
#define LINE_SIZE 100

/* Should i change it to int return type? */
int getMazeFromFile(const char* filename, Maze* maze)
{
    int c;
    int i,j; // might not need, delete later
    int row,col;
    char MazeInfo[LINE_SIZE];
    char delim[4] = " xX";
    char *infoToken, *endptr;
    FILE *fp;
    if(!(fp = fopen(filename,"r")))
    {
        perror("Não foi possivel abrir o trtrttarquivo.");
        return(EXIT_FAILURE);
    }
    
    /* Checando se o arquivo não está vazio */
    if(isEmptyFile(fp))
    {
        perror("Arquivo vazio.");
        return(EXIT_FAILURE);
    }

    /* Lê a linha que contém o tamanho do labirinto,
     separa em tokens e converte para inteiro 
     antes de atribuir na struct */
    fgets(MazeInfo,LINE_SIZE,fp);
    newline_remover(MazeInfo);
    infoToken = strtok(MazeInfo,delim);
    maze->sizeX = strtol(infoToken,&endptr,10);
    infoToken = strtok(NULL,delim);
    maze->sizeY = strtol(infoToken,&endptr,10);

    /* Lê a linha que contém as coordenadas
     da entrada e saída do labirinto, separa em tokens
     e converte para inteiro antes de atribuir na struct */
    fgets(MazeInfo,LINE_SIZE,fp);
    check_newline(MazeInfo);
    infoToken = strtok(MazeInfo,delim);
    maze->startX = strtol(infoToken,&endptr,10);
    infoToken = strtok(NULL,delim);
    maze->startY = strtol(infoToken,&endptr,10);
    infoToken = strtok(NULL,delim);
    maze->endX = strtol(infoToken,&endptr,10);
    infoToken = strtok(NULL,delim);
    maze->endY = strtol(infoToken,&endptr,10);

    /* Criação da matriz que receberá o labirinto,
     com error handling em caso de falha de alocação*/
    if((maze->maze = create_2d_array(maze->sizeX,maze->sizeY))==NULL)
    {
        perror("Falha na alocação da matriz.");
        return(EXIT_FAILURE);
    }

    /* Loop de leitura e atribuição do labirinto nas posições da matriz */
    row = col = 0;
    while((c = fgetc(fp))!=EOF)
    {
        /* Caso sejam caracteres válidos */
        if(c == '0' || c == '#')
        {
            maze->maze[row][col] = c;
            col++;
        }

        /* Caso chegue o fim de uma linha */
        else if (c = '\n')
        {
            row++;
            col = 0;
        }

        /* Caso o caractere lido seja inválido */
        else
        {
            /* Dealocar aqui ou no main?? eis a questão */
            free_2d_array(maze->maze,maze->sizeX);
            perror("Caractere invalido no layout do labirinto.");
            return(EXIT_FAILURE);   
        }
    }
    return(EXIT_SUCCESS);
}

char ** create_2d_array(int rows, int cols)
{
    char **new_2d_array = malloc(rows * sizeof(char*));
    if(new_2d_array!=NULL)
    {
        for(int i = 0; i < rows; i++)
        {
            new_2d_array[i] = malloc(cols * sizeof(char));
            if(new_2d_array[i] == NULL)
                return NULL;
        }
        return new_2d_array;
    }
    else
        return NULL; 
}

void free_2d_array(char ** array, int rows)
{
    for(int i = 0; i < rows; i++) free(array[i]);
    free(array);
}

int isEmptyFile(FILE *fp)
{
    int size;
    fseek(fp,0,SEEK_SET);
    size = ftell(fp);
    fseek(fp,0,SEEK_SET);
    if(size > 0)
        return 1;
    return 0;
}