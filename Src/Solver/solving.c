#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * Allows to display/print a sudoku grid
 *
 * @param grid     The sudoku grid that we want to display/print
 ******************************************************************************/
void print_sudoku(unsigned char grid[9][9])
{
    for (unsigned char x = 0; x < 9; x++)
    {
        if(x == 3 || x == 6)
            printf("\n");
        for (unsigned char y = 0; y < 9; y++)
        {
            if(y == 3 || y == 6)
                printf(" ");
            printf("%d", grid[x][y]);
        }
        printf("\n");
    }
}

/*******************************************************************************
 * Allows to check if a number can be placed in this grid at [row][col] position
 *
 * @param grid     The sudoku grid
 * @param row      The row of the sudoku grid
 * @param col      The col of the sudoku grid
 * @param num      The number that we want to check if it can be placed
 * @return int     0 if the number can't be placed here else 1
 ******************************************************************************/
int can_be_placed(unsigned char grid[9][9], unsigned char row, unsigned char col, unsigned char num)
{
    for (unsigned char x = 0; x <= 8; x++)
        if (grid[row][x] == num)
            return 0;
    
    for (unsigned char x = 0; x <= 8; x++)
        if (grid[x][col] == num)
            return 0;
 
    unsigned char startRow = row - row % 3, startCol = col - col % 3;
   
    for (unsigned char i = 0; i < 3; i++)
        for (unsigned char j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return 0;
 
    return 1;
}

/*******************************************************************************
 * Allows to solve a sudoku grid
 *
 * @param grid     The sudoku grid that we want to solve
 * @param row      The row of the sudoku grid (for recursive call)
 * @param col      The col of the sudoku grid (for recursive call)
 * @return int     0 if the sudoku grid doesn't have solution else 1
 ******************************************************************************/
int solve_sudoku(unsigned char grid[9][9], unsigned char row, unsigned char col)
{
    if (row == 9 - 1 && col == 9)
        return 1;
    if (col == 9)
    {
        row++;
        col = 0;
    }
    if (grid[row][col] > 0)
        return solve_sudoku(grid, row, col + 1);
    for (unsigned num = 1; num <= 9; num++)
    {
        if (can_be_placed(grid, row, col, num))
        {
            grid[row][col] = num;
            if (solve_sudoku(grid, row, col + 1))
                return 1;
        }
        grid[row][col] = 0;
    }
    return 0;
}