/*  
Name : Suman Kafle
CS 241 
Project 4 : Sudoku Solver
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 9

#define MAX_INPUT_LENGTH 100

/* to check the subgrids if there is same number in the subgrids */
int checkSubgrid(int arr[SIZE][SIZE], int row, int col, int val)
{
  int i, j;
  int subgridRow = row - row % 3;
  int subgridCol = col - col % 3;

  /* checking the subgrid */
  for (i = subgridRow; i < subgridRow + 3; i++)
    {
      for (j = subgridCol; j < subgridCol + 3; j++)
	  {
	    if (arr[i][j] == val && (i != row || j != col))
	    {
	      return 1;
	    }
	  }
    }
  return 0;
}

/*  to check for the row and column if the number is repeataed */
int checkRowAndColumn(int arr[SIZE][SIZE], int row, int col,int number)
{
  int i, j;
  int val = number;

  /* checking the row */
  for (i = 0; i < SIZE; i++)
  {
    if (arr[row][i] == val && i != col)
	{
	  return 1;
	}
  }

  /* checking the column */
  for (j = 0; j < SIZE; j++)
  {
    if(arr[j][col] == val && j != row)
	{
	  return 1;
    }
  }
  return 0;
}

/*  to return the error if the number are repeated whether in subgrids or row and column */
int errorCheck( int ard[9][9])
{
  int b,c;

  for (  b = 0; b< 9; b++)
  {
    for (c = 0; c< 9; c++)
	{
	  if (ard[b][c]!= '.')
	  {
		/* to return 0 if repeated number is found in subgrids or row and column*/
	    if (checkRowAndColumn(ard,b,c,ard[b][c]) == 1 || checkSubgrid(ard,b,c,ard[b][c]) == 1)
		{
		  return 0;
		}
	  }
	}
  }
  /* return 1 if error is not foud*/
  return 1;
}


/*  to check if the number are placed in right place */
int isValidPlacement(int board[][SIZE], int number, int row, int column)
{
  return !(checkRowAndColumn(board, row, column, number) ||
	checkSubgrid(board,  row, column, number));
}

/*  to solve the sudoku board */
int solveBoard(int board[][SIZE])
{
  int row, column;
  char numberToTry;
  for (row = 0; row < SIZE; row++)
  {
    for (column = 0; column < SIZE; column++)
	{
	  if (board[row][column] == '.')
	  {
	    for (numberToTry = '1'; numberToTry <= '9'; numberToTry++)
		{
		  if (isValidPlacement(board, numberToTry, row, column))
		  {
		    board[row][column] = numberToTry;
		    if (solveBoard(board))
			{
			  return 1;
			}
		    else
			{
			  board[row][column] = '.';
			}
		  }
		}
	    return 0;
	  }
	}
  }
  return 1;
}

/*  to print the board of the sudoku*/
void printBoard(int board[][SIZE])
{
  int row,column;
  for (row = 0; row < SIZE; row++)
  {
    for (column = 0; column < SIZE ; column++)
	{
	  if (isdigit(board[row][column]))
	  {
	    printf("%d", board[row][column] - '0');
	  }
	  else
	  {
	    printf(".");
	  }
	}
  }
  printf("\n");
}
/* function to check if the given input is valid by chechking whether it is digit and . or not*/
int isValidInput(char input[100])
{
  int i;
  /* if the input don't ahve 82 character it will return 0*/
  if(strlen(input) != 82)
  {
    return 0;
  }
  for (i = 0; i < strlen(input)-1; i++) 
  {
	/* if the input is whether digit and . or not */
    if (!isdigit(input[i]) &&  input[i] != '.') 
    {
      return 0;
    }
  }
  return 1;
}

int main()
{
  char input[MAX_INPUT_LENGTH];
  int i, j,  k = 0;
  int board[9][9];

  /* to take input from the user */
  while(fgets(input, MAX_INPUT_LENGTH, stdin))
  {
    k = 0;
    for (i = 0; i<strlen(input); i ++)
	{
	  printf("%c", input[i]);
	}
	/* to print error if the given input is not valid*/
    if ( !isValidInput(input))
	{
	  printf("Error\n\n");
	  continue;
	}
	else
	{
	  /* to convert input to board */
	  for (i = 0; i < 9; i++)
	  {
	    for (j = 0; j < 9; j++)
		{
		  board[i][j] = input[k];
		  k++;
		}
	  }
	  /* to print error if error is found*/
	  if ( errorCheck(board) == 0)
	  {
	    printf("Error\n\n");
	    continue;
	  }
	}

	/* Solving  the sudoku puzzle */
	if (solveBoard(board))
	{
	  /* printing  the solved puzzle */
	  printBoard(board);
	  printf("\n");
	  continue;
	}

	/* to print there is no solution if it does any give any solution*/
	else
	{
	  printf("No solution\n\n");
	  continue;
	}
  }
  return 0;
}
