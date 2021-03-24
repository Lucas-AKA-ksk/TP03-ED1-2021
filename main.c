#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "maze.h"


int main(int argc, char const *argv[])
{
    if(argc < 3)
    {
        perror("Menos argumentos do que o esperado.");
        exit(EXIT_FAILURE);
    }
    else if (argc > 3)
    {
        perror("Mais argumentos do que o esperado.");
        exit(EXIT_FAILURE);
    }
    
    Maze maze;
    stack solution;
    
    if(getMazeFromFile(argv[1],&maze)!=EXIT_FAILURE)
    {
        /* Printa o labirinto na tela */
        for (size_t i = 0; i < maze.sizeX; i++)
        {
            for (size_t j = 0; j < maze.sizeY; j++)
                printf("[%c]",maze.maze[i][j]);
            printf("\n");
        } 

        /* Pilha solution recebe a solução, ou NULL caso não haja uma solução */
        solution = solveMaze_DFS(maze);
        if(solution!=NULL)
        {
            printf("\nCaminho encontrado!");
            saveSolutionToFile(argv[2],maze,solution);
            endStack(solution);
        }
        else
            printf("\nO labirinto fornecido não possui uma solução.");
        free_2d_array(maze.maze,maze.sizeX);    
    }
    return 0;
}