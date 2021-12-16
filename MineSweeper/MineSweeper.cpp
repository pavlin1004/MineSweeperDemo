#include <iostream>
#include <stdlib.h>
using namespace std;
const int BOMBS_COUNT = 10;
const int GRID_BORDERSIZE = 8;
void RevealNearZero(int elementscondition[][GRID_BORDERSIZE],int grid[][GRID_BORDERSIZE],int xCoordinate,int yCoordinate)
{
    if (grid[xCoordinate][yCoordinate] == 0)
    {
        for (int i = xCoordinate - 1;i <= xCoordinate + 1;i++)
        {
            for (int j = yCoordinate - 1;j <= yCoordinate + 1;j++)
            {
                if (i >= 0 && j >= 0 && i <= GRID_BORDERSIZE && j <= GRID_BORDERSIZE)
                {                  
                    RevealNearZero(elementscondition,grid, i, j);
                    elementscondition[i][j] = 1;
                }
            }
        }
    }
}
int NearbyBombCount(int grid[][GRID_BORDERSIZE], int coordinateX, int coordinateY)
{
    int elementValue = 0;
    if (grid[coordinateX][coordinateY] != -1)
    {
        for (int i = coordinateX - 1;i <= coordinateX + 1;i++)
        {
            for (int j = coordinateY - 1;j <= coordinateY + 1;j++)
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
void GenerateBombs(int bombCoordinates[10],int grid[][GRID_BORDERSIZE],int firstXCoordinate,int firstYcoordinate)
{
    int currentXCoordinate,currentYCoordinate;  
    for (int i = 0;i < BOMBS_COUNT;i++)
    {           
            int isUnique = true;
            currentXCoordinate = rand() % 9;
            currentYCoordinate = rand() % 9;
            for (int j = 0;j < i;j++)
            {             
                if (bombCoordinates[j]/10 == currentXCoordinate&&bombCoordinates[j]%10==currentYCoordinate)
                {
                    isUnique = false;
                    break;
                }
                else
                {
                    for (int i = firstXCoordinate - 1;i <= firstXCoordinate + 1;i++)
                    {
                        for (int j = firstYcoordinate -1 ;j <= firstYcoordinate + 1;j++)
                        {
                            if (i >= 0 && j >= 0 && i <= GRID_BORDERSIZE && j <= GRID_BORDERSIZE)
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
                bombCoordinates[i] = currentXCoordinate*10+currentYCoordinate;
            }
            else i--;
    }
    for (int i = 0;i < BOMBS_COUNT;i++)
    {
        grid[bombCoordinates[i] / 10][bombCoordinates[i] % 10] = -1;
    }
}
void GenerateGrid(int grid[][GRID_BORDERSIZE], int bombCoordinates[10],int firstXCoordinate,int firstYcoordinate,int elementsCondition[][GRID_BORDERSIZE])
{
    grid[firstXCoordinate][firstYcoordinate] = 0;
    elementsCondition[firstXCoordinate][firstYcoordinate] = 1;
    GenerateBombs(bombCoordinates,grid,firstXCoordinate,firstYcoordinate);
    for (int i = 0;i <= GRID_BORDERSIZE;i++)
    {
        for (int j = 0;j <= GRID_BORDERSIZE;j++)
        {         
                grid[i][j] = NearbyBombCount(grid, i, j);           
        }
    }
}
void DisplayGrid(int grid[][GRID_BORDERSIZE], int elementsCondition[][GRID_BORDERSIZE])
{
    for (int i = 0;i <9;i++)
    { 
        for (int j = 0;j <9;j++)
        {
            if (elementsCondition[i][j] == 0)
                cout << "X   ";
            else if (elementsCondition[i][j] == -1)
            {
                cout << "M   ";
            }
            else
            {
                cout << grid[i][j] << "   ";
            }
        }
        cout << endl;
    } 
}
void Reveal(int grid[][GRID_BORDERSIZE],int coordinateX,int coordinateY, int bombCoordinates[10],int elementConditionCheckGrid[][GRID_BORDERSIZE])
{
    if (elementConditionCheckGrid[coordinateX][coordinateY] == 0)
    {
        elementConditionCheckGrid[coordinateX][coordinateY] = 1;
        RevealNearZero(elementConditionCheckGrid,grid,coordinateX,coordinateY);
    }
    else
    {
        cout << "You have already revealed this position";
    }

}
void Mark(int grid[][GRID_BORDERSIZE],int coordinateX,int coordinateY)
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
bool CheckForDefeat(int xCoordinate,int yCoordinate,int bombCoordinates[10])
{
    for (int i = 0;i <= 8;i++)
    {
        for (int j = 0;j <= 8;j++)
        {
            if (bombCoordinates[i] / 10 == xCoordinate && bombCoordinates[i] % 10 == yCoordinate)
            {
                return true;
            }
        }
    }
    return false;
}
bool CheckForWin(int elementsCondition[][GRID_BORDERSIZE], int bombCoordinates[10])
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
    while (true)
    {
        int grid[GRID_BORDERSIZE][GRID_BORDERSIZE] = {};
        int elementConditionCheckGrid[GRID_BORDERSIZE][GRID_BORDERSIZE] = {};
        int bombCoordinates[10] = {};
        for (int i = 0;i <=GRID_BORDERSIZE;i++)
        {
            for (int j = 0;j <= GRID_BORDERSIZE;j++)
            {
                elementConditionCheckGrid[i][j] = 0;
            }
        }
        DisplayMessages();
        int firstCoordinate, secondCoordinate;char action;
        cin >> firstCoordinate >> secondCoordinate >> action;
        GenerateGrid(grid,bombCoordinates, firstCoordinate, secondCoordinate,elementConditionCheckGrid);
        //RevealNearZero(elementConditionCheckGrid, grid, firstCoordinate, secondCoordinate);
        for (int i = 0;i < 9;i++)
        {
            for (int j = 0;j < 9;j++)
            {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
        DisplayGrid(grid,elementConditionCheckGrid);
        cout << endl;
        
        while (true)
        {  
            DisplayMessages();
            cin >> firstCoordinate >> secondCoordinate >> action;
            if (action == 'r')
            {
                
                if (CheckForDefeat(firstCoordinate,secondCoordinate, bombCoordinates) == true)
                {
                    cout << "You lost!!!" << endl;;
                    cout << "If you want to play a new game type: n" << endl;
                    cout << "If you want to stop playing type anything else" << endl;
                    break;
                }
                else
                {
                    Reveal(grid, firstCoordinate, secondCoordinate, bombCoordinates, elementConditionCheckGrid);
                }
                if (CheckForWin(elementConditionCheckGrid, (int*)bombCoordinates) == true)
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
            DisplayGrid(grid, elementConditionCheckGrid);
        }
        char playOrNot;
        cin >> playOrNot;
        if (playOrNot != 'n')
        {
            break;
        }
    }
    return 0;
}
