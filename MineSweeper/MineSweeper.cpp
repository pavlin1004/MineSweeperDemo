#include <iostream>
#include <stdlib.h>
using namespace std;
const int BOMBS_COUNT = 10;
const int GRID_BORDERSIZE = 9;
void RevealNearZero(int elementsRevealed[GRID_BORDERSIZE][GRID_BORDERSIZE],int xCoordinate,int yCoordinate)
{
    if (elementsRevealed[xCoordinate][yCoordinate] == 0)
    {
        for (int i = xCoordinate - 1;i <= xCoordinate + 1;i++)
        {
            for (int j = yCoordinate + 1;j <= yCoordinate - 1;j--)
            {
                if (i >= 0 && j >= 0 && i <= 8 && j <= 8)
                {
                    if (elementsRevealed[i][j] == 0)
                    {
                        RevealNearZero(elementsRevealed, xCoordinate, yCoordinate);                      
                    }
                    elementsRevealed[i][j] = 1;
                }
            }
        }
    }
}
int NearbyBombCount(int grid[GRID_BORDERSIZE][GRID_BORDERSIZE], int coordinateX, int coordinateY)
{
    int elementValue = 0;
    if (grid[coordinateX][coordinateY] != -1)
    {
        for (int i = coordinateX - 1;i <= coordinateX + 1;i++)
        {
            for (int j = coordinateY + 1;j <= coordinateY - 1;j--)
            {
                if (i >= 0 && j >= 0 && i <= 8 && j <= 8)
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
void GenerateBombs(int bombCoordinates[BOMBS_COUNT],int grid[GRID_BORDERSIZE][GRID_BORDERSIZE],int firstXCoordinate,int firstYcoordinate)
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
                else
                {
                    for (int i = firstXCoordinate - 1;i <= firstXCoordinate + 1;i++)
                    {
                        for (int j = firstYcoordinate + 1;j <= firstYcoordinate - 1;j--)
                        {
                            if (i >= 0 && j >= 0 && i <= 8 && j <= 8)
                            {
                                if (bombCoordinates[j] / 10 == i && bombCoordinates[j] % 10 == j)
                                {
                                    isUnique = false;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            if (isUnique)
            {
                bombCoordinates[i] = currentCoordinates;
            }
            else i--;
    }
    for (int i = 0;i < BOMBS_COUNT;i++)
    {
        grid[bombCoordinates[i] / 10][bombCoordinates[i] % 10] = -1;
    }
}
void GenerateGrid(int grid[GRID_BORDERSIZE][GRID_BORDERSIZE], int bombCoordinates[BOMBS_COUNT],int firstXCoordinate,int firstYcoordinate)
{
    grid[firstXCoordinate][firstYcoordinate] = 0;
    GenerateBombs(bombCoordinates, grid,firstXCoordinate,firstYcoordinate);
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
                cout <<"|"<< "*";
            else cout <<"|"<< condition[i][j];
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
void Mark(int grid[GRID_BORDERSIZE][GRID_BORDERSIZE],int coordinateX,int coordinateY)
{
    if (grid[coordinateX][coordinateY] == 0)
    {
        grid[coordinateX][coordinateY] == -1;
    }
    else if (grid[coordinateX][coordinateY] == 1)
    {
        cout << "You have already revealed this position";
    }
    else cout << "You have already marked this element";
}
void DisplayMessages()
{
    cout << "Reveal a postion by typing: [coordinate1] [coordinate2] r" << endl;
    cout << "Mark a bomb by typing:[coordinate1] [coordinate2] b" << endl;
    cout << "Unmark a bomb by typing:[coordinate1] [coordinate2] u" << endl;
}
int main()
{  
    bool newGame = true;
    while (newGame)
    {
        int  grid[GRID_BORDERSIZE][GRID_BORDERSIZE] = {};
        int elementConditionCheckGrid[GRID_BORDERSIZE][GRID_BORDERSIZE] = {};
        int bombCoordinates[10] = {};
        for (int i = 0;i < +10;i++)
        {
            for (int j = 0;j < +10;j++)
            {
                elementConditionCheckGrid[i][j] = 0;
            }
        }
        DisplayMessages();
        int firstCoordinate, secondCoordinate;char action;
        cin >> firstCoordinate >> secondCoordinate >> action;
        GenerateGrid(grid, bombCoordinates,firstCoordinate,secondCoordinate);
        DisplayGrid(grid, elementConditionCheckGrid);
        RevealNearZero(elementConditionCheckGrid, firstCoordinate, secondCoordinate);
        bool endOfGame = false;
        bool win = false;
        while (endOfGame = false)
        {  
            DisplayMessages();
            cin >> firstCoordinate >> secondCoordinate >> action;
            if (action == 'r')
            {
                Reveal(grid, firstCoordinate, secondCoordinate, bombCoordinates, elementConditionCheckGrid);
            }
            if (action == 'b')
            {
                Mark(grid, firstCoordinate, secondCoordinate);
            }
        }
    }
}
