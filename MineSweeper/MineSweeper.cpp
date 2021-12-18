#include <iostream>
#include <stdlib.h>
#include <random>
#include <ctime>
using namespace std;
const int BOMBS_COUNT = 10;
const int GRID_BORDERSIZE = 9;
void RevealNearZero(int elementscondition[][GRID_BORDERSIZE], int grid[][GRID_BORDERSIZE], int xCoordinate, int yCoordinate)
{
    if (grid[xCoordinate][yCoordinate] == 0)
    {
        for (int i = xCoordinate - 1;i <= xCoordinate + 1;i++)
        {
            for (int j = yCoordinate-1;j <= yCoordinate + 1;j++)
            {
                if (i >= 0 && j >= 0 && i <= 8 && j <= 8)
                {
                    if (elementscondition[i][j] == 0)
                    {
                        elementscondition[i][j] = 1;
                        RevealNearZero(elementscondition, grid, i, j);
                    }
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
}//Working
void GenerateBombs(int bombCoordinates[10], int grid[][GRID_BORDERSIZE], int firstXCoordinate, int firstYcoordinate)
{
    int currentXCoordinate, currentYCoordinate;
    for (int i = 0;i < BOMBS_COUNT;i++)
    {
        int isUnique = true;
        int counter = 0;
        for (int t = 0;t <= counter;t++)
        {
            currentXCoordinate = rand() % 9;
            currentYCoordinate = rand() % 9;
            for (int x = firstXCoordinate - 1;x <= firstXCoordinate + 1;x++)
            {
                for (int y = firstYcoordinate - 1;y <= firstYcoordinate + 1;y++)
                {
                    if (x >= 0 && y >= 0 && x <= 8 && y <= 8)
                    {
                        if (currentXCoordinate == x && currentYCoordinate == y)
                        {
                            counter++;
                        }
                    }
                }
            }
        }
        for (int j = 0;j < i;j++)
        {
            if (bombCoordinates[j] / 10 == currentXCoordinate && bombCoordinates[j] % 10 == currentYCoordinate)
            {
                isUnique = false;
                break;
            }
        }
        if (isUnique == true)
        {
            bombCoordinates[i] = currentXCoordinate * 10 + currentYCoordinate;
            grid[currentXCoordinate][currentYCoordinate] = -1;
        }
        else i--;
    }
}
void GenerateGrid(int grid[][GRID_BORDERSIZE], int bombCoordinates[10], int firstXCoordinate, int firstYcoordinate, int elementsCondition[][GRID_BORDERSIZE])
{
    grid[firstXCoordinate][firstYcoordinate] = 0;
    elementsCondition[firstXCoordinate][firstYcoordinate] = 1;
    GenerateBombs(bombCoordinates, grid, firstXCoordinate, firstYcoordinate);
    for (int i = 0;i < GRID_BORDERSIZE;i++)
    {
        for (int j = 0;j < GRID_BORDERSIZE;j++)
        {
            int isBomb = false;
            for (int k = 0;k < BOMBS_COUNT;k++)
            {
                if (bombCoordinates[k] / 10 == i && bombCoordinates[k] % 10 == j)
                {
                    isBomb = true;
                }
            }
            if (!isBomb)
            {
                grid[i][j] = NearbyBombCount(grid, i, j);
            }
        }
    }
    RevealNearZero(elementsCondition, grid, firstXCoordinate, firstYcoordinate);
}
void DisplayUngeneratedGrid( int elementsCondition[][GRID_BORDERSIZE])
{
    cout << "0   1   2   3   4   5   6   7   8   9" << endl;
    cout << " _____________________________________" << endl;
    for (int i = 0;i < 9;i++)
    {
        cout << i + 1 << "|    ";
        for (int j = 0;j < 9;j++)
        {
            if (elementsCondition[i][j] == 0)
                cout << "X    ";
            else if (elementsCondition[i][j] == -1)
            {
                cout << "B    ";
            }
        }
        cout << endl;
    }
}
void DisplayGrid(int grid[][GRID_BORDERSIZE], int elementsCondition[][GRID_BORDERSIZE])
{
    cout << "0   1   2   3   4   5   6   7   8   9"<<endl;
    cout << " _____________________________________" << endl;
    for (int i = 0;i < 9;i++)
    {
        cout << i + 1 << "|    ";
        for (int j = 0;j < 9;j++)
        {
            if (elementsCondition[i][j] == 0)
                cout << "X    ";
            else if (elementsCondition[i][j] == -1)
            {
                cout << "B    ";
            }
            else if (grid[i][j] == 0)
            {
                cout <<((char)220)<<"    ";
            }
            else
            {
                cout << grid[i][j] << "    ";
            }
        }
        cout << endl;
    }
}
void Reveal(int grid[][GRID_BORDERSIZE], int coordinateX, int coordinateY, int bombCoordinates[10], int elementConditionCheckGrid[][GRID_BORDERSIZE])
{
    if (elementConditionCheckGrid[coordinateX][coordinateY] == 0|| elementConditionCheckGrid[coordinateX][coordinateY] == -1)
    {
        elementConditionCheckGrid[coordinateX][coordinateY] = 1;
        RevealNearZero(elementConditionCheckGrid, grid, coordinateX, coordinateY);
    }
    else
    {
        cout << "You have already revealed this position";
    }

}
void Mark(int elementConditionCheckGrid[][GRID_BORDERSIZE], int coordinateX, int coordinateY)
{
    if (elementConditionCheckGrid[coordinateX][coordinateY] == 0)
    {
        elementConditionCheckGrid[coordinateX][coordinateY] = -1;
    }
    else if (elementConditionCheckGrid[coordinateX][coordinateY] == 1)
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
bool CheckForDefeat(int xCoordinate, int yCoordinate, int bombCoordinates[10])
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
    //Opening messages
    cout <<"TO WIN YOU HAVE TO MARK ALL 10 BOMBS AND REVEAL ALL OTHER ELEMENTS";
    cout << "IF YOU REVEAL A BOMB YOU LOSE THE GAME";
    //Ensures bom will be on different positions each game
    srand(time(0));
    //Game starts
    while (true)
    {
        //Grid to generate
        int grid[GRID_BORDERSIZE][GRID_BORDERSIZE] = {};
        //Has value 1 if element is revealed
        //Has value 0 if element is covered
        //Has value -1 if element is marked as bomb
        int elementConditionCheckGrid[GRID_BORDERSIZE][GRID_BORDERSIZE] = {};
        //Array of 10 randomly generated bomb coordinates
        int bombCoordinates [10];
        //Makes all elements covered by deafult
        for (int i = 0;i < GRID_BORDERSIZE;i++)
        {
            for (int j = 0;j < GRID_BORDERSIZE;j++)
            {
                elementConditionCheckGrid[i][j] = 0;
            }
        }
        
        int firstCoordinate, secondCoordinate;char action;
        while (action != 'r')
        {
            DisplayMessages();
            cin >> firstCoordinate >> secondCoordinate >> action;
            while (firstCoordinate < 1 || firstCoordinate>9 || secondCoordinate < 1 || secondCoordinate>9 || action != 'r' || action != 'b')
            {
                if (action == 'b' || action == 'c')
                {
                    cout << "Input coordinate should be between 1-9";
                }
                if (action != 'b' || action != 'c')
                {
                    cout << "Input command should be 'r'-for reveal OR 'm' for marking a bomb";
                }
                cin >> firstCoordinate >> secondCoordinate >> action;
            }
            if (action == 'b')
            {
                elementConditionCheckGrid[firstCoordinate - 1][secondCoordinate - 1] = -1;
                DisplayUngeneratedGrid(elementConditionCheckGrid);
            }
        }
            GenerateGrid(grid, bombCoordinates, firstCoordinate - 1, secondCoordinate - 1, elementConditionCheckGrid);
            for (int i = 0;i < 9;i++)
            {
                for (int j = 0;j < 9;j++)
                {
                    cout << grid[i][j] << " ";
                }
                cout << endl;
            }
            DisplayGrid(grid, elementConditionCheckGrid);
            cout << endl;
        while (true)
        {
            DisplayMessages();
            cin >> firstCoordinate >> secondCoordinate >> action;
            if (action == 'r')
            {

                if (CheckForDefeat(firstCoordinate - 1, secondCoordinate - 1, bombCoordinates) == true)
                {
                    cout << "You lost!!!" << endl;;
                    cout << "If you want to play a new game type: n" << endl;
                    cout << "If you want to stop playing type anything else" << endl;
                    break;
                }
                else
                {
                    Reveal(grid, firstCoordinate - 1, secondCoordinate - 1, bombCoordinates, elementConditionCheckGrid);
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
                Mark(elementConditionCheckGrid, firstCoordinate-1, secondCoordinate-1);
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