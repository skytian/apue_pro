#include<stdio.h>
#include<stdlib.h>

int islandPerimeter(int **grid, int gridRowSize, int gridColSize);
int main(){
    int **grid = (int **)malloc(4*sizeof(int *));
    for(int i = 0; i < 4; i++){
        grid[i] = (int*)malloc(4*sizeof(int));
        grid[i][0]=1;
        grid[i][1]=1;
        grid[i][2]=1;
        grid[i][3]=1;
    }
	int count = islandPerimeter(grid, 4, 4);
	printf("count:%d\n", count);
}
int islandPerimeter(int **grid, int gridRowSize, int gridColSize) {
    int i = 0, j = 0;
    int num = 0;
    printf("i:%d j:%d grid[i][j]:%d \n", i, j, grid[i][j]);
    for(i = 0; i < gridRowSize; i++)
        for(j = 0; j < gridColSize; j++){
            if(grid[i][j] == 1){
                num += 4;
                printf("i:%d j:%d grid[i][j]:%d \n", i, j, grid[i][j]);
                if(i != 0 && grid[i-1][j] == 1)
                    num--;
                if(i != gridRowSize-1 && grid[i+1][j] == 1)
                    num--;
                if(j != 0 && grid[i][j-1] == 1)
                    num--;
                if(j != gridColSize-1 && grid[i][j+1] == 1)
                    num--;
            }
        }
    return num;

}
