#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

int main(int argc, char const *argv[])
{
    /* code some stuff, probably... */
    Maze maze;
    
    printf("%s",argv[1]);//teste
    if(getMazeFromFile(argv[1],&maze)!=EXIT_FAILURE)
    {
        printf("\nNICE!\n");
    }
    return 0;
}