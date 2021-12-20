#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <windows.h>
using namespace std;
const int BOMBS_COUNT = 10;
const int GRID_BORDERSIZE = 9;
HANDLE hConsole;
/// <summary>
/// When currently revealed element has value 0 all elements around it are also being revealed
/// If some of the revealed elements have value 0 all elemnts around it are revealed too
/// </summary>
/// <param name="elementsConditionCheckGrid">
/// Element has value: 0 if not revealed
///                   -1 if marked as bomb
///                    1 if revealed
/// </param>
/// <param name="grid">
/// 9*9 matrix with all elements value
/// if element is bomb it has value -1
/// </param>
/// <param name="xCoordinate"></param>
/// <param name="yCoordinate"></param>
void RevealNearZero(int elementsConditionCheckGrid[][GRID_BORDERSIZE], int grid[][GRID_BORDERSIZE], int xCoordinate, int yCoordinate)
{
    if (grid[xCoordinate][yCoordinate] == 0)
    {
        for (int i = xCoordinate - 1;i <= xCoordinate + 1;i++)
        {
            for (int j = yCoordinate - 1;j <= yCoordinate + 1;j++)
            {
                if (i >= 0 && j >= 0 && i < GRID_BORDERSIZE && j < GRID_BORDERSIZE)
                {
                    if (elementsConditionCheckGrid[i][j] == 0)
                    {
                        elementsConditionCheckGrid[i][j] = 1;
                        RevealNearZero(elementsConditionCheckGrid, grid, i, j);
                    }
                }
            }
        }
    }
}
/// <summary>
/// Increase element value in the grid by 1 for each bomb around it
/// Used for grid generation
/// </summary>
/// <param name="grid"></param>
/// <param name="coordinateX"></param>
/// <param name="coordinateY"></param>
/// <returns>
/// Updated grid element value
/// </returns>
int NearbyBombCount(int grid[][GRID_BORDERSIZE], int coordinateX, int coordinateY)
{
    int elementValue = 0;
    if (grid[coordinateX][coordinateY] != -1)
    {
        for (int i = coordinateX - 1;i <= coordinateX + 1;i++)
        {
            for (int j = coordinateY - 1;j <= coordinateY + 1;j++)
            {
                if (i >= 0 && j >= 0 && i < GRID_BORDERSIZE && j < GRID_BORDERSIZE)
                {
                    if (grid[i][j] == -1)
                    {
                        elementValue++;
                    }
                }
            }
        }
    }
    return elementValue;
}
/// <summary>
/// Randomly generates 10 DIFFERENT bomb coordinates
/// </summary>
/// <param name="bombCoordinates">
/// Array[10] that keeps all bombs coordinates in format xCoordinate*10+yCoordinate 
/// xCoordinate = array[k]/10 yCoordinate = array[k]%10
/// </param>
/// <param name="grid"></param>
/// <param name="firstXCoordinate"></param>
/// <param name="firstYcoordinate"></param>
void GenerateBombs(int bombCoordinates[BOMBS_COUNT], int grid[][GRID_BORDERSIZE], int firstXCoordinate, int firstYcoordinate)
{
    int currentXCoordinate, currentYCoordinate;
    for (int i = 0;i < BOMBS_COUNT;i++)
    {
        bool isUnique = true;
        int loopsCounter = 1;
        for (int t = 0;t < loopsCounter;t++)
        {
            currentXCoordinate = rand() % 9;
            currentYCoordinate = rand() % 9;
            for (int x = firstXCoordinate - 1;x <= firstXCoordinate + 1;x++)
            {
                for (int y = firstYcoordinate - 1;y <= firstYcoordinate + 1;y++)
                {
                    if (x >= 0 && y >= 0 && x < GRID_BORDERSIZE && y < GRID_BORDERSIZE)
                    {
                        if (currentXCoordinate == x && currentYCoordinate == y)
                        {
                            loopsCounter++;
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
/// <summary>
/// When game starts the first element to be revealed ALWAYS has value 0
/// Then generates 10 bombs 
/// All elements with coordinates around the first revealed element cannot be bombs
/// When bombs are already generated all other elements values are being calculated 
/// </summary>
/// <param name="grid"></param>
/// <param name="bombCoordinates"></param>
/// <param name="firstXCoordinate"></param>
/// <param name="firstYcoordinate"></param>
/// <param name="elementsConditionCheckGrid"></param>
void GenerateGrid(int grid[][GRID_BORDERSIZE], int bombCoordinates[BOMBS_COUNT], int firstXCoordinate, int firstYcoordinate, int elementsConditionCheckGrid[][GRID_BORDERSIZE])
{
    grid[firstXCoordinate][firstYcoordinate] = 0;
    elementsConditionCheckGrid[firstXCoordinate][firstYcoordinate] = 1;
    GenerateBombs(bombCoordinates, grid, firstXCoordinate, firstYcoordinate);
    for (int i = 0;i < GRID_BORDERSIZE;i++)
    {
        for (int j = 0;j < GRID_BORDERSIZE;j++)
        {
            bool isBomb = false;
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
    RevealNearZero(elementsConditionCheckGrid, grid, firstXCoordinate, firstYcoordinate);
}
/// <summary>
/// Displays the grid
/// All covered element are displayed with ---> X
/// All marked elements are displayed with ---> B
/// </summary>
/// <param name="grid"></param>
/// <param name="elementsConditionCheckGrid"></param>
/// <param name="gameOver">
/// False by default
/// When game ends ---> gameover = true ---> All bombs are displayed in red --->All marked incorrectly marked elements are displayed in blue  
/// </param>
void DisplayGrid(int grid[][GRID_BORDERSIZE], int elementsConditionCheckGrid[][GRID_BORDERSIZE], bool gameOver = false)
{  
    cout << "     1   2   3   4   5   6   7   8   9" << endl;
    cout << "  _____________________________________" << endl;
    for (int i = 0;i < 9;i++)
    {
        cout << i + 1 << "|   ";
        for (int j = 0;j < 9;j++)
        {
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            if (gameOver == true && grid[i][j] == -1)
            {
                SetConsoleTextAttribute(hConsole, 12);
                cout << "§   ";
            }
            else 
            {
                if (elementsConditionCheckGrid[i][j] == 0)
                {
                    cout << "X   ";
                }
                else if (elementsConditionCheckGrid[i][j] == -1)
                {
                    if (gameOver == true)
                    {
                        SetConsoleTextAttribute(hConsole, 9);
                    }
                    cout << "B   ";
                }
                else if (grid[i][j] == 0)
                {
                    cout << "    ";
                }
                else
                {
                    cout << grid[i][j] << "   ";
                }
            }
            SetConsoleTextAttribute(hConsole, 15);
        }
        cout << endl;
    }
}
/// <summary>
/// Reveals element with the given coordinates
/// If element has value zero all elements around it are revealed
/// If element is already revealed brings out appropriate message
/// </summary>
/// <param name="grid"></param>
/// <param name="coordinateX"></param>
/// <param name="coordinateY"></param>
/// <param name="bombCoordinates"></param>
/// <param name="elementsConditionCheckGrid"></param>
void Reveal(int grid[][GRID_BORDERSIZE], int coordinateX, int coordinateY, int bombCoordinates[BOMBS_COUNT], int elementsConditionCheckGrid[][GRID_BORDERSIZE])
{
    if (elementsConditionCheckGrid[coordinateX][coordinateY] == 0 || elementsConditionCheckGrid[coordinateX][coordinateY] == -1)
    {
        elementsConditionCheckGrid[coordinateX][coordinateY] = 1;
        RevealNearZero(elementsConditionCheckGrid, grid, coordinateX, coordinateY);
    }
    else
    {
        cout << "You have already revealed this position" << endl;
    }
}
/// <summary>
/// Marked an element as a bomb
/// </summary>
/// <param name="elementsConditionCheckGrid"></param>
/// <param name="coordinateX"></param>
/// <param name="coordinateY"></param>
void Mark(int elementsConditionCheckGrid[][GRID_BORDERSIZE], int coordinateX, int coordinateY)
{
    if (elementsConditionCheckGrid[coordinateX][coordinateY] == 0)
    {
        elementsConditionCheckGrid[coordinateX][coordinateY] = -1;
    }
    else if (elementsConditionCheckGrid[coordinateX][coordinateY] == 1)
    {
        cout << "You have already revealed this position" << endl;
    }
    else cout << "You have already marked this element" << endl;
}
void DisplayMessages()
{
    cout << "Reveal a postion by typing: [coordinate1] [coordinate2] r" << endl;
    cout << "Mark a bomb by typing:[coordinate1] [coordinate2] b" << endl;
}
/// <summary>
/// If bomb is revealed game over
/// </summary>
/// <param name="xCoordinate"></param>
/// <param name="yCoordinate"></param>
/// <param name="bombCoordinates"></param>
/// <returns>
/// True if bomb is revealed
/// </returns>
bool CheckForDefeat(int xCoordinate, int yCoordinate, int bombCoordinates[BOMBS_COUNT])
{
    for (int i = 0;i < GRID_BORDERSIZE;i++)
    {
        for (int j = 0;j < GRID_BORDERSIZE;j++)
        {
            if (bombCoordinates[i] / 10 == xCoordinate && bombCoordinates[i] % 10 == yCoordinate)
            {
                return true;
            }
        }
    }
    return false;
}
/// <summary>
/// If all bombs are marked and all other elements revealed the game is over
/// </summary>
/// <param name="grid"></param>
/// <param name="elementsConditionCheckGrid"></param>
/// <param name="bombCoordinates"></param>
/// <returns>
/// True if all bombs are marked and all elements revealed
/// </returns>
bool CheckForWin(int grid[][GRID_BORDERSIZE],int elementsConditionCheckGrid[][GRID_BORDERSIZE], int bombCoordinates[BOMBS_COUNT])
{  
    for (int i = 0;i < GRID_BORDERSIZE;i++)
    {
        for (int j = 0;j < GRID_BORDERSIZE;j++)
        {
            if (grid[i][j]==-1&&elementsConditionCheckGrid[i][j] != -1)
            {
                return false;
            }
            else if (elementsConditionCheckGrid[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}
int main()
{
    //Ensures the bombs will be at different positions each game
    srand(time(0));
    //Opening messages
    cout << "                                          M I N E S W E E P E R" << endl;
    cout << "                 _______________________________________________________________________" << endl;
    cout << "                      TO WIN YOU HAVE TO MARK ALL 10 BOMBS AND REVEAL ALL OTHER ELEMENTS" << endl;
    cout << "                                  IF YOU REVEAL A BOMB YOU LOSE THE GAME" << endl;
    cout << "                 _______________________________________________________________________" << endl;
    //Game
    while (true)
    {
        //Grid to generate
        int grid[GRID_BORDERSIZE][GRID_BORDERSIZE] = {};
        //Has value  1 if element is revealed
        //Has value  0 if element is covered
        //Has value -1 if element is marked as bomb
        int elementsConditionCheckGrid[GRID_BORDERSIZE][GRID_BORDERSIZE] = { 0 };
        //Array of 10 randomly generated bomb coordinates
        int bombCoordinates[10];
        //Displays grid with all elements(ungenerated) covered
        DisplayGrid(grid, elementsConditionCheckGrid, false);
        //Decalring variebles
        int firstCoordinate, secondCoordinate;
        char action;
        //Game starts
        while (true)
        {
            //Displays guyding messages
            DisplayMessages();
            cout << "--->";
            cin >> firstCoordinate >> secondCoordinate >> action;
            if (firstCoordinate >= 1 || firstCoordinate <= GRID_BORDERSIZE || secondCoordinate >= 1 || secondCoordinate <= GRID_BORDERSIZE)
            {
                if (action == 'b')
                {
                    Mark(elementsConditionCheckGrid, firstCoordinate - 1, secondCoordinate - 1);
                    DisplayGrid(grid, elementsConditionCheckGrid, false);
                }
                else if (action == 'r')
                {
                    break;
                }
                else
                {
                    cout << "Action should be 'r' for revealing a position OR 'b' for marking a bomb" << endl;
                }
            }
            else
            {
                cout << "Coordinates should be between 1 and 9" << endl;
            }
        }
        //If coordinates are correct and action is revealing position the progrmam generates a 9x9 grid
        GenerateGrid(grid, bombCoordinates, firstCoordinate - 1, secondCoordinate - 1, elementsConditionCheckGrid);
        //Displays generated grid with currently revealed elements
        DisplayGrid(grid, elementsConditionCheckGrid);
        cout << endl;
        //Start to manipulate the generated grid
        while (true)
        {
            DisplayMessages();
            cout << "--->";
            cin >> firstCoordinate >> secondCoordinate >> action;
            //Checks for correct coordinates           
            if (firstCoordinate > 0 || firstCoordinate <= GRID_BORDERSIZE || secondCoordinate > 0 || secondCoordinate <= GRID_BORDERSIZE)
            {
                if (action == 'r')
                {
                    //If you try to reveal bomb you lose 
                    //Game ends
                    if (CheckForDefeat(firstCoordinate - 1, secondCoordinate - 1, bombCoordinates) == true)
                    {
                        cout << "-----------------------------------------------------------" << endl;
                        cout << "You lost!!!" << endl;;
                        DisplayGrid(grid, elementsConditionCheckGrid, true);
                        cout << "If you want to play a new game type: n" << endl;
                        cout << "If you want to stop playing type anything else" << endl;
                        break;

                    }
                    //If the element is not a bomb it gets revealed
                    else
                    {
                        Reveal(grid, firstCoordinate - 1, secondCoordinate - 1, bombCoordinates, elementsConditionCheckGrid);
                    }
                    //Show the grid with revealed elements
                }
                else if (action == 'b')
                {
                    //Marks an element
                    Mark(elementsConditionCheckGrid, firstCoordinate - 1, secondCoordinate - 1);
                }
                //Incorrect action input
                else
                {
                    cout << "Action should be 'r' for revealing a position OR 'b' for marking a bomb" << endl;
                }
                DisplayGrid(grid, elementsConditionCheckGrid);
            }
            //Incorrect coordinates input
            else
            {
                cout << "Coordinates should be between 1 and 9" << endl;
            }
            if (CheckForWin(grid, elementsConditionCheckGrid, bombCoordinates) == true)
            {
                cout << "You won!!!" << endl;;
                cout << "If you want to play a new game type: n !" << endl;
                cout << "If you want to stop playing type anything else" << endl;
                break;
            }
        }
        char playOrNot;
        cout << "--->";
        cin >> playOrNot;
        //New game?
        if (playOrNot != 'n')
        {
            //Program closes
            break;
        }
        else
        {
            cout << "-----------------------------------------------NEW GAME--------------------------------------------------" << endl;
        }
    }
    return 0;
}