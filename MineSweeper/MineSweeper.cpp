#include <iostream>
#include <stdlib.h>
using namespace std;
const int BOMBS_COUNT = 10;
const int GRID_BORDERSIZE = 9;
void RevealNearZero(int grid[GRID_BORDERSIZE][GRID_BORDERSIZE])
{

}
int NearbyBombCount(int grid[GRID_BORDERSIZE][GRID_BORDERSIZE], int coordinateX, int coordinateY)
{
    int elementValue = 0;
    if (grid[coordinateX][coordinateY] != -1)
    {
        for (int i = coordinateX - 1;i < +coordinateX + 1;i++)
        {
            for (int j = coordinateY + 1;j <= coordinateY - 1;j--)
            {
                if (i >= 0 && j >= 0 && i < 9 && j <= 9)
                {
                    if (i == coordinateX && j == coordinateY) continue;
                    else
                    {
                        if (grid[i][j] == -1)
                        {
                            elementValue++;
                        }
                    }
                }
            }
        }
    }
    return elementValue;
}
void GenerateBombs(int bombCoordinates[BOMBS_COUNT],int grid[GRID_BORDERSIZE][GRID_BORDERSIZE])
{
    int currentCoordinates;   
    for (int i = 0;i < BOMBS_COUNT;i++)
    {           
            int isUnique = true;
            currentCoordinates = rand() % 90;
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
void GenerateGrid(int grid[GRID_BORDERSIZE][GRID_BORDERSIZE], int bombCoordinates[BOMBS_COUNT])
{
    GenerateBombs(bombCoordinates, grid);
    for (int i = 0;i < BOMBS_COUNT;i++)
    {
        for (int j = 0;j < BOMBS_COUNT;j++)
        {
            if (i != 0 && i != 9 && j != 0 && j != 9)
            {
                grid[i][j] = NearbyBombCount(grid, i, j);
            }
        }
    }
}
void DisplayGrid(int grid[GRID_BORDERSIZE][GRID_BORDERSIZE], int condition[GRID_BORDERSIZE][GRID_BORDERSIZE])
{
    for (int i = 0;i < +10;i++)
    {
        for (int j = 0;j < +10;j++)
        {
            if (condition[i][j] == 0)
                cout << "*";
            else cout << condition[i][j];
        }
        cout <<"|"<<endl<< "_________";
    }
}
int Reveal(int grid[GRID_BORDERSIZE][GRID_BORDERSIZE],int coordinateX,int coordinateY, int bombCoordinates[BOMBS_COUNT],int elementConditionCheckGrid[GRID_BORDERSIZE][GRID_BORDERSIZE])
{
    for (int i = 0;i <= BOMBS_COUNT;i++)
    {
        if (bombCoordinates[i] / 10 == coordinateX && bombCoordinates[i] % 10 == coordinateY)
        {
            return 0;
        }
    }
    if (elementConditionCheckGrid[coordinateX][coordinateY] == 0)
    {
        elementConditionCheckGrid[coordinateX][coordinateY] == 1;
    }
    else
    {
        cout << "You have already revealed this position";
    }
    return 1;
}
void Mark(int grid[GRID_BORDERSIZE][GRID_BORDERSIZE])
{
    //TODO
}
int main()
{  
    
    int  grid[GRID_BORDERSIZE][GRID_BORDERSIZE] = {};
    int elementConditionCheckGrid[GRID_BORDERSIZE][GRID_BORDERSIZE] = {};
    bool firstReveal = false;
    for (int i = 0;i < +10;i++)
    {
        for (int j = 0;j < +10;j++)
        {
            elementConditionCheckGrid[i][j] = 0;
        }
    }
    int bombCoordinates[BOMBS_COUNT] = {};
    GenerateBombs(bombCoordinates,grid);
}
