#include <stdio.h>
#include <stdlib.h>

//declare all functions
void printGrid();
int check (int row, int col);
void flag (int row, int col);
int checkWin();
void reveal(int row, int col);

//gridAI is the grid the player sees, while grid is the actual grid layout
int gridAI[10][10] = {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
                      '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
                      '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
                      '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
                      '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
                      '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
                      '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
                      '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
                      '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',
                      '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'};

int grid[10][10] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
                    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};

int main()
{
    //seed the random function
    srand(2);

    //declare all variables
    int mines, row, column;
    char command;

    //create the random layout for the mines
    for (int i = 0; i < 10; i++)
    {
        int x = rand() % 10;
        int y = rand() % 10;


        if (grid[x][y] != 'M')
        {
            grid[x][y] = 'M';
        }
        //if the selected square is already a mine, subtract one from the counter to allow it to run an extra iteration
        else
        {
            i--;
        }
    }

    //finalize the layout by calculating the number of mines in each square vicinity and assigning the squares said value
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            //reset the mine counter
            mines = 0;

            //skip the squares that contain a mine
            if (grid[i][j] != 'M')
            {

                //all the if statements below check if a square in the vicinity contains a mine, incrementing the mine
                //counter each time a mine is spotted
                if (grid[i-1][j] == 'M')
                {
                    if (i != 0)
                    {
                        mines++;
                    }
                }
                if (grid[i-1][j+1] == 'M')
                {
                    if (i != 0 && j != 9)
                    {
                        mines++;
                    }
                }
                if (grid[i-1][j-1] == 'M')
                {
                    if (j != 0 && i != 0)
                    {
                        mines++;
                    }
                }
                if (grid[i][j-1] == 'M')
                {
                    if (j != 0)
                    {
                        mines++;
                    }
                }
                if (grid[i][j+1] == 'M')
                {
                    if (j != 9)
                    {
                        mines++;
                    }
                }
                if (grid[i+1][j-1] == 'M')
                {
                    if (j != 0 && i != 9)
                    {
                        mines++;
                    }
                }
                if (grid[i+1][j] == 'M')
                {
                    if (i != 9)
                    {
                        mines++;
                    }
                }
                if (grid[i+1][j+1] == 'M')
                {
                    if (i != 9 && j != 9)
                    {
                        mines++;
                    }
                }
                //finally, assign each square the value of mines nearby as a character by adding 48,
                //as this is the ASCII value of 0
                grid[i][j] = mines + 48;
            }
        }
    }

    //this loop contains the game
    while (1)
    {
        //start by printing the grid and prompting the user for input
        printGrid();
        printf("Enter 'c' for check cell, 'f' for flag cell.\n\n"
               "Enter command & cell row col:");
        scanf("%c %d %d", &command, &row, &column);

        //if the user wishes to check the selected square, run the check() function. If the selected square is a mine,
        //break the loop and end the game
        if (command == 'c')
        {
            if (check(row, column) == 0)
            {
                break;
            }
        }
        //run the flag() function if the user wishes to flag the selected square
        else if (command = 'f')
        {
            flag(row, column);
        }

        //at the end of each iteration, check if the user has won the game with the checkWin() function
        if (checkWin() == 1)
        {
            break;
        }
    }
    return 0;
}

//This function prints gridAI to the terminal
void printGrid()
{
    printf("\n");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%c  ", gridAI[i][j]);
        }
        printf("\n");
    }
}

//this function checks if the square selected by the user is a mine or not.
int check (int row, int col)
{
    if (grid[row][col] == 'M')
    {
        printf("You hit a mine, game over.");
        return 0;
    }
    //if the selected square is not a mine, run the reveal() function to reveal all nearby 0 1 and 2 values
    else
    {
        reveal(row, col);
        return 1;
    }
}

// reveals all nearby 0 1 and 2 values
void reveal(int row, int col)
{
    if (row != 10 && col != 10)
    {
        //oly run this block of code if the current square is a 0
        if (grid[row][col] == '0')
        {
            //reveal the current square to the AI and mark it with an R in the actual grid to signify it has been revealed
            gridAI[row][col] = grid[row][col];
            grid[row][col] = 'R';

            //all if statements below ensure that the only squares being revealed are within the grid
            if (row != 9)
            {
                reveal(row+1, col);
            }
            if (col != 9)
            {
                reveal(row, col+1);
            }
            if (row != 0)
            {
                reveal(row-1, col);
            }
            if (col != 0)
            {
                reveal(row, col-1);
            }
            if (col != 0 && row != 0)
            {
                reveal(row - 1, col-1);
            }
            if (col != 0 && row != 9)
            {
                reveal(row +1, col-1);
            }
            if (col != 9 && row != 0)
            {
                reveal(row - 1, col+1);
            }
            if (col != 9 && row != 9)
            {
                reveal(row + 1, col+1);
            }

        }

        // if the square is not 0 or a mine, reveal it, but not the nearby squares
        else if (grid[row][col] > '0' && grid[row][col] < '7')
        {
            gridAI[row][col] = grid[row][col];
            grid[row][col] = 'R';
        }
    }
}

//this function flags the selected square
void flag (int row, int col)
{
    gridAI[row][col] = 'F';
}

//this function checks if the game has been won by checking if all non-mine squares have been revealed
int checkWin()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (grid[i][j] != 'R' || 'M')
            {
                return 0;
            }
        }
    }
    printf("You win");
    return 1;
}