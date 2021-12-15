#include <iostream>
#include <stdlib.h>
const int BOMBS_COUNT = 10;
const int GRID_BORDERSIZE = 9;
void GenerateBombs(int bombCoordinates[BOMBS_COUNT],int grid[GRID_BORDERSIZE][GRID_BORDERSIZE])
{
    int currentCoordinates;   
    for (int i = 0;i < BOMBS_COUNT;i++)
    {           
            int isUnique = true;
            currentCoordinates = rand() % 100;
            for (int j = 0;j < i;j++)
            {             
                if (bombCoordinates[j] == currentCoordinates)
                {
                    isUnique = false;
                    break;
                }
            }
            if (isUnique)
            {
                bombCoordinates[i] == currentCoordinates;
            }
            else i--;
    }
    for (int i = 0;i < BOMBS_COUNT;i++)
    {
        grid[bombCoordinates[i] / 10][bombCoordinates[i] % 10] = -1;
    }
}
void GenerateGrid(int gird[GRID_BORDERSIZE][GRID_BORDERSIZE])
{
    //TODO
}
void Reveal(int gird[GRID_BORDERSIZE][GRID_BORDERSIZE])
{
    //TODO
}
void Mark(int gird[GRID_BORDERSIZE][GRID_BORDERSIZE])
{
    //TODO
}
int main()
{
    int  grid[GRID_BORDERSIZE][GRID_BORDERSIZE] = {};
    int bombCoordinates[BOMBS_COUNT] = {};
    GenerateBombs(bombCoordinates,grid);
}
