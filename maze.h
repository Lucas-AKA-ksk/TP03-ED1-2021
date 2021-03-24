#ifndef MAZE_H_DEFINED
#define MAZE_H_DEFINED

typedef struct
{
    char **maze;
    int sizeX, sizeY;
    int startX, startY, endX, endY;
}Maze;

int getMazeFromFile(const char* filename, Maze* maze);

stack solveMaze_DFS(Maze maze);

int saveSolutionToFile(const char* filename, Maze maze,stack solution);

char ** create_2d_array(int rows, int cols);

void free_2d_array(char** array, int rows);

int isEmptyFile(FILE *fp);

#endif //MAZE_H_DEFINED