#include <iostream>
#include <stdlib.h>
using namespace std;
const int BOMBS_COUNT = 10;
const int GRID_BORDERSIZE = 8;
void RevealNearZero(int** elementsRevealed,int** grid,int xCoordinate,int yCoordinate)
{
    if (elementsRevealed[xCoordinate][yCoordinate] == 0)
    {
        for (int i = xCoordinate - 1;i <= xCoordinate + 1;i++)
        {
            for (int j = yCoordinate + 1;j <= yCoordinate - 1;j--)
            {
                if (i >= 0 && j >= 0 && i <= GRID_BORDERSIZE && j <= GRID_BORDERSIZE)
                {
                    if (grid[i][j] == 0)
                    {
                        RevealNearZero(elementsRevealed,grid, i, j);                      
                    }
                    elementsRevealed[i][j] = 1;
                }
            }
        }
    }
}
int NearbyBombCount(int** grid, int coordinateX, int coordinateY)
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
void GenerateBombs(int* bombCoordinates,int** grid,int firstXCoordinate,int firstYcoordinate)
{
    int currentCoordinates;   
    for (int i = 0;i < BOMBS_COUNT;i++)
    {           
            int isUnique = true;
            currentCoordinates = rand() % 89;
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
void GenerateGrid(int** grid, int* bombCoordinates,int firstXCoordinate,int firstYcoordinate,int** elementsCondition)
{
    grid[firstXCoordinate][firstYcoordinate] = 0;
    elementsCondition[firstXCoordinate][firstYcoordinate] = 1;
    GenerateBombs((int*)bombCoordinates, (int**)grid,firstXCoordinate,firstYcoordinate);
    for (int i = 0;i < BOMBS_COUNT;i++)
    {
        for (int j = 0;j < BOMBS_COUNT;j++)
        {         
                grid[i][j] = NearbyBombCount((int**)grid, i, j);           
        }
    }
}
void DisplayGrid(int** grid, int** elementsCondition)
{
    for (int i = 0;i <9;i++)
    {
        for (int j = 0;j <9;j++)
        {
            if (elementsCondition[i][j] == 0)
                cout <<"|"<< "*";
            else cout <<"|"<< elementsCondition[i][j];
        }
        cout << "|" << endl << "_ _ _ _ _ _ _ _ _" << endl;
    }
}
int Reveal(int** grid,int coordinateX,int coordinateY, int* bombCoordinates,int** elementConditionCheckGrid)
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
        elementConditionCheckGrid[coordinateX][coordinateY] = 1;
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
        grid[coordinateX][coordinateY] = -1;
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
}
bool CheckForDefeat(int** ekementsCondition,int* bombCoordinates)
{
    for (int i = 0;i <= 8;i++)
    {
        for (int j = 0;j <= 8;j++)
        {
            if (bombCoordinates[i] / 10 == i && bombCoordinates[i] % 10 == j)
            {
                return true;
            }
        }
    }
    return false;
}
bool CheckForWin(int** elementsCondition, int* bombCoordinates)
{
    for (int i = 0;i <= 8;i++)
    {
        for (int j = 0;j <= 8;j++)
        {
            if (bombCoordinates[i] / 10 == i && bombCoordinates[i] % 10 == j)
            {
                if (elementsCondition[i][j] != -1)
                {
                    return false;
                }
            }
            else
            {
                if (elementsCondition[i][j] != 1)
                {
                    return false;
                }
            }
        }
    }
    return true;
}
int main()
{  
    bool newGame = true;
    while (newGame)
    {
        int grid[GRID_BORDERSIZE][GRID_BORDERSIZE] = {};
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
        GenerateGrid((int**)grid, (int*)bombCoordinates, firstCoordinate, secondCoordinate,(int**)elementConditionCheckGrid);
        DisplayGrid((int**)grid, (int**)elementConditionCheckGrid);
        RevealNearZero((int**)elementConditionCheckGrid,(int**)grid, firstCoordinate, secondCoordinate);
        bool endOfGame = false;
        while (endOfGame = false)
        {  
            DisplayMessages();
            cin >> firstCoordinate >> secondCoordinate >> action;
            if (action == 'r')
            {
                Reveal((int**)grid, firstCoordinate, secondCoordinate, (int*)bombCoordinates, (int**)elementConditionCheckGrid);
                if (CheckForDefeat((int**)elementConditionCheckGrid, (int*)bombCoordinates) == true)
                {
                    cout << "You lost!!!" << endl;;
                    cout << "If you want to play a new game type: n" << endl;
                    cout << "If you want to stop playing type anything else" << endl;
                    break;
                }
                if (CheckForWin((int**)elementConditionCheckGrid, (int*)bombCoordinates) == true)
                {
                    cout << "You won!!!" << endl;;
                    cout << "If you want to play a new game type: n !" << endl;
                    cout << "If you want to stop playing type anything else" << endl;
                    break;
                }
            }
            if (action == 'b')
            {
                Mark(grid, firstCoordinate, secondCoordinate);
            }
        }
        char playOrNot;
        cin >> playOrNot;
        if (playOrNot != 'n')
        {
            newGame = false;
        }
    }
    return 0;
}
