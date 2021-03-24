#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "stack.h"
#include "utility.h"
#include "maze.h"
#define LINE_SIZE 100

/* explanatory comment here */
int getMazeFromFile(const char* filename, Maze* maze)
{
    int c;
    int row,col;
    char MazeInfo[LINE_SIZE];
    char delim[4] = " xX";
    char *infoToken, *endptr;
    FILE *fp;
    if(!(fp = fopen(filename,"r")))
    {
        perror("Não foi possivel abrir o arquivo.");
        return(EXIT_FAILURE);
    }
    
    /* Checando se o arquivo não está vazio */
    if(isEmptyFile(fp))
    {
        fclose(fp);
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
        fclose(fp);
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
            fclose(fp);
            free_2d_array(maze->maze,maze->sizeX);
            perror("Caractere invalido no layout do labirinto.");
            return(EXIT_FAILURE);   
        }
    }
    fclose(fp);
    return(EXIT_SUCCESS);
}

stack solveMaze_DFS(Maze maze)
{
    TSElement XYs;
    TLElement trvrsd_coord;
    stack path = createStack();
    list traversed = createList();

    /* Inicializa os elementos com as coordenadas do início
     do labirinto e insere na pilha e na lista */
    XYs.path_row = trvrsd_coord.row = maze.startX;
    XYs.path_col = trvrsd_coord.col =  maze.startY;
    push(path,XYs);
    insertAtTail(traversed,trvrsd_coord);

    while(path->size)
    {
        pop(path,&XYs);
        
        /* Caso as coordenadas XYs atuais sejam o fim do labirinto*/
        if (XYs.path_row == maze.endX && XYs.path_col == maze.endY)
        {
            push(path,XYs);
            endlist(traversed);
            return path;
        }
        /* Caso o caminho a esquerda (col-1) seja valido e ainda não tenha sido percorrido */
        else if (XYs.path_col-1 >= 0 && maze.maze[XYs.path_row][XYs.path_col-1] != '#' && !searchList(traversed,XYs.path_row,XYs.path_col-1))
        {
            push(path,XYs);
            XYs.path_col--;
            trvrsd_coord.row = XYs.path_row;
            trvrsd_coord.col = XYs.path_col;
            push(path,XYs);
            insertAtTail(traversed,trvrsd_coord);
        }
        /* Caso o caminho a direita (col+1) seja valido e ainda não tenha sido percorrido */
        else if (XYs.path_col+1 < maze.sizeY && maze.maze[XYs.path_row][XYs.path_col+1] != '#' && !searchList(traversed,XYs.path_row,XYs.path_col+1))
        {
            push(path,XYs);
            XYs.path_col++;
            trvrsd_coord.row = XYs.path_row;
            trvrsd_coord.col = XYs.path_col;
            push(path,XYs);
            insertAtTail(traversed,trvrsd_coord);
        }
        /* Caso o caminho acima (row-1) seja valido e ainda não tenha sido percorrido */
        else if (XYs.path_row-1 >= 0 && maze.maze[XYs.path_row-1][XYs.path_col] != '#' && !searchList(traversed, XYs.path_row-1,XYs.path_col))
        {
            push(path,XYs);
            XYs.path_row--;
            trvrsd_coord.row = XYs.path_row;
            trvrsd_coord.col = XYs.path_col;
            push(path,XYs);
            insertAtTail(traversed,trvrsd_coord);
        }
        /* Caso o caminho a direita (row+1) seja válido e ainda não tenha sido percorrido */
        else if (XYs.path_row+1 < maze.sizeX && maze.maze[XYs.path_row+1][XYs.path_col] != '#' && !searchList(traversed,XYs.path_row+1,XYs.path_col))
        {
            push(path,XYs);
            XYs.path_row++;
            trvrsd_coord.row = XYs.path_row;
            trvrsd_coord.col = XYs.path_col;
            push(path,XYs);
            insertAtTail(traversed,trvrsd_coord);
        }
    }
    endStack(path);
    return NULL;
}

int saveSolutionToFile(const char* filename, Maze maze,stack solution)
{
    TSElement XYs;
    FILE *fp;

    /* Abertura do arquivo, com error handling */
    if(!(fp = fopen(filename,"w")))
    {
        perror("Não foi possivel abrir o arquivo.");
        return(EXIT_FAILURE);
    }

    /* Printando o labirinto solucionado no arquivo
     onde o caminho percorrido é representado por zeros 
     e as demais posições, sejam paredes ou caminhos invalidos, 
     representados por '+' */
    fprintf(fp,"Caminho percorrido pelo algoritmo:\n\n");
    for (size_t i = 0; i < maze.sizeX; i++)
    {
        for (size_t j = 0; j < maze.sizeY; j++)
        {
            if(searchStack(solution,i,j))
                fprintf(fp,"[%c]",maze.maze[i][j]);
            else
                fprintf(fp,"[+]");
        }   
        fprintf(fp,"\n");
    }
    
    /* Printando as coordenadas percorridas para solucionar o labirinto 
     no arquivo, em ordem do inicio ao fim (o que requer que a ordem dos 
     elementos da pilha seja invertida) */
    fprintf(fp,"\nCoordenadas percorridas em ordem:\n");
    reverseStack(solution);
    while(solution->top){
        pop(solution,&XYs);
        fprintf(fp,"\n[%d][%d]",XYs.path_row,XYs.path_col);
    }
    
    printf("\nA solução do labirinto foi salva no arquivo %s",filename);
    fclose(fp);

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
    fseek(fp,0,SEEK_END);
    size = ftell(fp);
    fseek(fp,0,SEEK_SET);
    if(size > 0)
        return 0;
    return 1;
}