#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "life.h"

int countNeighbors (int x, int y, int rows, int cols, char **grid){
    int liveNeighbors = 0;

    for(int j = -1; j <= 1; j++){
        for(int k = -1; k <= 1; k++){
            if(!(j == 0 && k == 0)){

                int newX = x + j;
                int newY = y + k;

                if(newX >= 0 && newX < rows && newY >= 0 && newY < cols){
                    if(grid[newX][newY] == 'X'){
                        liveNeighbors++;                       
                    }                   
                }               
            }           
        }
    }
    return liveNeighbors;
}

void updateGrid(int rows, int cols, char  **grid){
    char newGrid[rows][cols];

    for(int x = 0; x < rows; x++){
        for(int y =  0; y < cols; y++){

            int neighborCount = countNeighbors(x, y, rows, cols, grid);

            if(grid[x][y] == LIVE){
                if(neighborCount < 2 || neighborCount > 3){
                    newGrid[x][y] = DEAD;
                } else {
                    newGrid[x][y] = LIVE;                   
                }
            } else {
                if(neighborCount == 3){
                    newGrid[x][y] = LIVE;
                } else {
                    newGrid[x][y] = DEAD;                   
                }               
            }           
        }
    }

    for(int j = 0; j < rows; j++){
        for(int k = 0; k < cols; k++){
            grid[j][k] = newGrid[j][k];                    
        }
    }
}

void printGrid(int rows, int cols, char **grid){
    for(int x = 0; x < rows; x++){
        for(int y = 0; y < cols; y++){
            if(grid[x][y] == LIVE){
                printf("%c", 'X');                   
            }
            if(grid[x][y] == DEAD){
                printf("%c", ' ');
            }
        }
        putchar('\n');
    }
}

int main(int argc, char *argv[]){

    if(argc < 2 || 3 < argc){
        printf("Error! Too many arguments or too little");
        return -1;
    }

    char **grid = parse_life(argv[1]);

    if(grid == NULL){
        return -1;
    }
    
    int gen = atoi(argv[2]);
    
    for(int x = 1; x <= gen; x++){
        updateGrid(GRIDY, GRIDX, grid);     
    }

    printGrid(GRIDY, GRIDX, grid);

    free_grid(grid);

    return 0;
    
}
