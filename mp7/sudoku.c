#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

/*
 * MP 7 Introductory Paragraph:
 * In this MP, I implemented a C program that solves a Sudoku puzzle using recursive backtracking.
 * I first implemented four helper functions:
 *
 * is_val_in_row() helps me to check if a certain value exists within any cell in a specific row.
 * is_val_in_column() helps me to check if a certain value exists within any cell in a specific column.
 * Both of these functions use a loop to iterate over a row/column while keeping the other constant.
 * This allows both functions to check if a value exists within a cell in a row or column.
 *
 * I also implemented is_val_in_3x3_zone(). This function checks if a value is in a specific 3x3 grid.
 * Using the location of the cell I am checking, I first found the starting row and column of the grid the cell is located in.
 * I then looped over the cells in that grid to check if the value already existed.
 *
 * To combine these three helper functions, I implemented is_val_valid(). This uses is_val_in_row(), is_val_in_column(), and 
 * is_val_in_3x3_zone() to check if the value already exists in a place it can be placed.
 * If not, the value is valid and the functions returns 1, otherwise it returns 0 if the value is invalid.
 *
 * Finally, I implemented the solve_sudoku() function.
 * The function first finds an empty cell by iterating over cells in each row and column. 
 * It finds an empty location by searching for a cell that holds the value 0.
 * After finding an empty cell, it checks if each possible value from 1 to 9 at that cell works.
 * The function checks if the possible value is valid using the is_val_valid() helper function.
 * If it is valid, it uses recursive backtracking to check the solution. It changes the grid by assigning the value to the empty cell.
 * It then uses recursion to call the solve_sudoku() funciton with the new grid. 
 * If the recursive call resulted in a correct solution, it returns true.
 * If the recursive call did not result in a correct solution, then the possible value is incorrect and cell is changed back to 0 and it returns False.
 * The function will repeat this process to test if each possible value is correct.
 * If no empty cells are found, the puzzle is completed and the function returns 1.
 * 
 * I used the three provided files to compile and test my code.
 */



// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9); //Makes sure the row is valid

  // BEG TODO
  for(int j=0; j<9; j++){ //Loop through columns while row is constant
    if (sudoku[i][j] == val) { //Check if value exists in the row
      return 1; //If it exists, return 1
    }
  }
  return 0; //If value does not exist in row, return 0
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9); //Makes sure the column is valid

  // BEG TODO
  for(int i=0; i<9; i++){ //Loop through rows while column is constant
    if (sudoku[i][j] == val) { //Check if value exists in the column
      return 1; //If it exists, return 1
    }
  }
  return 0; //If value does not exist in column, return 1
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9); //Makes sure the cell is in a valid row
  
  // BEG TODO
  int startRow, startCol; //Initialize variables for the start of the row
  startRow = i - (i%3); //Calculate the first row of the 3x3 grid which the cell is located at
  startCol = j - (j%3); //Calculate the first column of the 3x3 grid which the cell is located at
  for(int a=0; a<3; a++){ //Check each row of that grid
    for (int b=0; b<3; b++){ //Check each column of that grid
      if (sudoku[startRow+a][startCol+b] == val){ //Check if the value exists in a cell in the 3x3 grid
        return 1; //If the value exists in a cell in the 3x3 grid, return 1
      }
    }
  }
  return 0; //If the value does not exist in any cell in the 3x3 grid, return 0
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9); //Makes sure the row and column is valid

  // BEG TODO
  if (!(is_val_in_row(val, i, sudoku))){ //Check if the value exists within cells in the same row
    if (!(is_val_in_col(val, j, sudoku))){ //Check if the value exists within cells in the same column
      if (!(is_val_in_3x3_zone(val, i, j, sudoku))){ //Check if the value exists within cells in the 3x3 grid
        return 1; //Return 1 if the value does not already exist and is valid to be placed
      }
    }
  }
  return 0; //Return 0 if the value cannot be placed since it already exists within a cell in the row/column/3x3grid
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i, j; //Initialize iterative variables
	
  for(i=0; i<9; i++){ //Find empty cell by looping through rows
		for (j=0; j<9; j++){ //Find empty cell by looping through columns

			if (sudoku[i][j] != 0) continue; //Skip cell if it already holds a number (not zero)

			for (int val=1; val<=9; val++){ //Check possibility of values from 1 to 9
				if (!(is_val_valid(val, i, j, sudoku))) continue; //Skip the value if it is invalid (cannot be placed at that cell)
				sudoku[i][j]=val; //Place the value at the cell if it is valid
				if(solve_sudoku(sudoku)) return 1; //Use recursion to test the solution with that cell
				sudoku[i][j] = 0; //If incorrect, empty the cell to test the next possibility
			}
		return 0; //Backtracking step, return 0 if the attempted solution does not work
		}
	}
	return 1; //No empty cells are found, solution found
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





