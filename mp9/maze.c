#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/* MP9: Introduction Paragraph
 * In this MP, I implemented a maze solver utilizing depth-first recursion.
 * The input files provided represent a layout of the maze, where the first two numbers display the height and width of the maze
 * The rest of the text file displays the structure: %s are walls, blank spaces are empty cells that you can move through
 * S represents the start of the maze and E represents the end of the maze. The goal is to go from S to E.
 * Furthermore, the program solves the maze and outputs a text file similar to the input.
 * This output file will display the path of the solution where a * shows the correct path traveled
 * A ~ also shows a path traveled by the program but it was not part of the correct solution
 * 
 * Four functions were implemented for this maze solver: createMaze(), destroyMaze(), printMaze(), and solveMazeDFS().
 *
 * In the createMaze() function I opened the text file given as input and allocated memory for each row and column in the maze
 * I then created a pointer to a maze_t structure and used the values of the height and width of the file to create the maze
 * I iterated through each cell in the maze and copied the structure from the input file to the maze_t array of cells.
 * I also set the startRow, startColumn, endRow, and endColumn of the maze which shows where S and E are.
 * The function then closes the input file and returns the maze_t pointer.
 * 
 * For destroyMaze(), the goal was to free all the memory allocated for the maze in createMaze()
 * To accomplish this, I freed memory in the reverse order that it was allocated in createMaze()
 * I first freed each set of cell rows, then the cells array, and then I freed the memory allocated by the structure;
 *
 * In printMaze(), I iterated over each cell in the maze structure and printed it out.
 * I also added a new line after each row.
 *
 * In solveMazeDFS(), I used recursion to find a path that would solve the maze if possible.
 * I followed the Depth-First-Search algorithm suggested in the MP9 Wiki:
 * I first checked the base case where either the goal state is reached where the cell is at the end of the maze
 * or if the cell is at an invalid position within the maze. 
 * So I checked if the cell was out of maze bounds and then checked if the cell was not empty or at the start/end locations
 * If not, I marked the current cell as part of the solution path by changing the empty cell to a *.
 * I then used recursion to call solveMazeDFS() again but moved in a different direction.
 * I first moved to the left cell, then the right, then up, and then down.
 * If either move resulted in moving to a cell that was part of a solution path, then the function would return true.
 * If no move resulted in a correct solution, the function would backtrack.
 * It backtracks by unmarking the current cell as part of the solution and changing it to a ~ to show that the cell was visited.
 * The function the ends by returning false if the current cell is not part of the solution.
 *
 * Utilizing these four functions allowed me to create the maze structure, destroy it, print out the state of the maze, and use
 * depth-first recursion along with backtracking to solve the maze.
 *
 */

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    FILE *strm = fopen(fileName, "r"); //Open textfile with maze_t structure
    maze_t * maze = malloc(sizeof(maze_t)); //allocate memory for maze_t structure

    int h = 0;
    int w = 0;
    char newline;
    fscanf(strm, "%d %d", &h, &w); //retreive row and col length from text file
    maze->height = h; //set maze height
    maze->width = w; //set maze width
    
    maze-> cells = malloc(sizeof(maze->cells)*(maze->height)); //allocate memory for cells row

    
    int i, j; //initialize i and j
    for (i=0; i<maze->height; i++){ //iterate over each row
        maze->cells[i] = malloc(sizeof(maze->cells[i]) * maze->width); //allocate memory for cells size of each row
    }
    fscanf(strm, "%c", &newline); //ignore the newline after the width/height labels

    for (i=0; i<maze->height; i++){ //iterate through maze rows
        for (j=0; j<maze->width; j++){ //iterate through maze columns
            fscanf(strm, "%c", &newline); //ignore newline
            maze->cells[i][j] = newline;
            if (maze->cells[i][j] == 'S'){ //if cell is at the start, set startRow and startColumn
                maze->startRow = i;
                maze->startColumn = j;
            }
            if (maze->cells[i][j] == 'E'){ //if cell is at the end, set endRow and endColumn
                maze->endRow = i;
                maze->endColumn = j;
            }
        }
        fscanf(strm, "%c", &newline); //ignore newline after each row
    }
    fclose(strm); //close the strm file
    return maze; //return maze pointer
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    //free mallocs created in createMaze (reverse order)
    int i;
    for (i=0; i<maze->height; i++){
        free(maze->cells[i]); //free cells memory
    }
    free(maze->cells); //free struct
    free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int rows = maze->height; //set rows
    int cols = maze->width; //set cols
    int i, j;
    for (i=0; i<rows; i++){
        for (j=0; j<cols; j++){
            printf("%c", maze->cells[i][j]); //iterate over each row/col and print cell
        }
        printf("\n"); //add a newline after each row
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    if (col<0 || col>=maze->width || row<0 || row>=maze->height){ //check if col and row are within maze bounds
        return 0; //if they are outside of maze bounds, return false
    }
    if (maze->cells[row][col] != 'S' && maze->cells[row][col] != 'E' && maze->cells[row][col] != ' '){ //check if cell is not empty or at start/end
        return 0; //return false if cell is not empty
    }
    if (maze->cells[row][col] == 'E'){ //Check if row/col reaches end of the maze
        maze->cells[maze->startRow][maze->startColumn] = 'S'; //Reset the maze starting position
        return 1; //Return true if it reached the end of the maze
    }

    maze->cells[row][col]='*'; //set row/col cell as part of the solution path in maze

    if (solveMazeDFS(maze, col-1, row)){ //check left of current cell
        return 1; //if correct, return true
    }
    if (solveMazeDFS(maze, col+1, row)){ //check right of current cell
        return 1; //if correct, return true
    }
    if (solveMazeDFS(maze, col, row+1)){ //check above current cell
        return 1; //if correct, return true
    }
    if (solveMazeDFS(maze, col, row-1)){ //check below current cell
        return 1; //if correct, return true
    }
    maze->cells[row][col]='~'; //mark cell at row/col as visited instead of part of solution if it is not correct
    return 0; //return false
}
