/* Intro Paragraph MP6:
 *
 * In this MP, I implemented three functions that contribute to a Game of Life program.
 * This game is played in a two-dimensional grid of cells that follows four rules.
 * 1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
 * 2. Any live cell with two or three live neighbours lives on to the next generation.
 * 3. Any live cell with more than three live neighbours dies, as if by over-population.
 * 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
 * In this MP, the grid space is formed using a one-dimesional array, where a cell with the value 1 is alive and 0 is dead.
 * 
 * The first function I implemented is countLiveNeighbor. 
 * The function took in the one-dimensional board array, the size of the board, and the location of the cell to check.
 * The function checks which cells directly surrounding the cell are alive and returns the total number of live cells.
 * I wrote this function by using nested loops to iterate through the rows and columns surrounding the specificed cell.
 * I would check if the cells around were 1 (alive) or 0 (dead).
 * If alive, I added the value to an integer sum and returned that value as the output.
 * 
 * The second function I implemented was updateBoard.
 * This function implemented the four rules for the game defined above.
 * updateBoard utilizes the countLiveNeighbor function to check the neighbors of each cell at the current step.
 * It then updates the board with conditions that match the four rules.
 * This function doesn't output any value since it changes the grid used to display cells.
 *
 * The last function I implemented was aliveStable.
 * This function checks if the arrangement of cells in the grid result in no change for the next step.
 * This means that the game has ended since the cells are no longer able to change.
 * To accomplish this, I utilized a one-dimensional copy of the array and changed the cells in the grid as if they were in the next step.
 * I then compared the cells in the copy to the cells in the current grid. If there is no change, the board is stable.
 * The function would output 1 if the board was stable and would not change and 0 if the board would change and was unstable.
 * 
 */


/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    int alive = 0; // Initialize count of live neighbors
    int current; //Initialize value to hold the status of the cell it is checking

    for(int i=row-1; i<=row+1; i++){ //Iterate through the rows directly above and below the cell
        if((i >= 0) && (i < boardRowSize)){ //Check to make sure the row exists within the board
            for(int j=col-1; j<=col+1; j++){ //Iterate through the columns directly left and right of the cell
                if((j >= 0) && (j < boardColSize)){ //Check to make sure the column exists within the board
                    if ((i != row) || (j != col)){ //Make sure the cell being checked is a neighboring cell
                        current = board[i*boardColSize + j]; //Set current to the cell value. Accesses the value in the one dimensional array using game_board[row_index * column_width + column_index]
                        if(current == 1){ //Check if the cell is alive
                            alive++; //If alive, increment the counter
                        }
                    }
                }
            }
        }
    }
    return alive; //Return the total number of live neighboring cells
    
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    int check; //Initialize variable to count the number of neighbors of a cell
    int current; //Initialize variable to check if the current cell is dead or alive
    
    int length = boardRowSize*boardColSize; //Length of the one-dimensional board array will be the # of rows times the # of columns
    int copy[length]; //Create a copy of the current grid of cells
    for (int k=0; k<length; k++) {
        copy[k] = board[k]; //Iterate and copy over the value of the current grid of cells to the alternate array.
    }

    for(int i=0; i<boardRowSize; i++){ //Iterate through each row
        for(int j=0; j<boardColSize; j++){ //Iterate through each column
            check = countLiveNeighbor(copy, boardRowSize, boardColSize, i, j); //Set check to the number of live cells neighboring the current cell.
            current = board[i*boardColSize + j]; //Set current to the value of the current cell
            if ((current == 1) && (!(check == 2 || check == 3))){ //If the cell is alive and does not have 2 or 3 live neighbors, the cell dies
                board[i*boardColSize + j] = 0;// //Set value of current cell to 0 to change its status to dead
            } else if ((current == 0) && (check == 3)) { //If the cell is dead and has 3 live neighbors, the dead cell turns alive.
                board[i*boardColSize + j] = 1; //Set value of current cell to 1 to change its status to alive
            }
        }
    }

}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    int length = boardRowSize*boardColSize; //Length of the one-dimensional grid array will be # of rows * # of columns
    int copy[length]; //Create an alternate array to hold a copy of the grid
    for (int k=0; k<length; k++) {
        copy[k] = board[k]; //Copy the values of cells in the current grid to the alternate grid
    }
    updateBoard(copy, boardRowSize, boardColSize); //Change the step of the alternate array which is a copy of the board (this changes the copy and not the current grid)
    for (int k=0; k<length; k++) { //Iterate through each cell in both the copy and the current grid
        if (board[k] != copy[k]){ //Check if any cell is different
            return 0; //If the cells are different and the current board does not stay the same for the next step, return 0 (unstable)
        }
    }
    return 1; //If the cells were the same, and the current board did not change for the next step, return 1 (stable)
}

				
				
			

