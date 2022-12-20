#include "game.h"

/* Intro Paragraph: MP8
 * In this MP, I developed the game 2048. I implemented this game to be played on a variable sized grid.
 * My make_game function utilized pointers to create the game structure. This was done using a typedef structure
 * which was implemented in game.h. Furthermore, the grid was designed so that empty cells would have a value of -1.
 * The function remake game uses the established pointer values from the make_game function and resets the grid by iterating
 * over the cells and assigning each cell an empty value.
 * The get_cell function uses row major order indexing of a 1 dimensional array to return a pointer of the cell.
 * In the game structure, cell is another type implemented to act as an integer.
 * In the move functions, each function followed a structure of sliding cells if possible, then merging, then sliding again.
 * Each slide function iterates over the cells and checks if they have an empty cell in the direction they are sliding in. If yes,
 * The function changes the grid to shift each cell over. Merge checks if any pair of cells in the direction they are sliding are the same.
 * If they are the same, the merge function combines the two cell values and changes the previous cell to an empty one.
 * This means the functions have to slide again, to ensure that all cells have been shifted in the specified direction.
 * Each function required me to implement separate iterative loops to check pairs of cells in the direction they merged in.
 * The final function legal_move checked if a move was possible by sliding or merging cells at the current point in the grid.
 * This was done by checking if any empty spaces remained, which would allow the cells to slide. Or if any cell had a duplicate value
 * in the cells adjacent to it. This would allow the grid to change by merging.
 */


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows = rows; //set rows
    mygame->cols = cols; //set columns
    for (int i=0; i<rows; i++){ //loop over rows and columns and change each cell to an empty cell
        for (int j=0; j<cols; j++){
            mygame->cells[(i*cols) + j] = -1;
        }
    }
    mygame->score = 0; //set score to 0
    return mygame; //return the pointer
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
    (*_cur_game_ptr)->rows = new_rows; //change the rows attribute to the new row value
    (*_cur_game_ptr)->cols = new_cols; //change the columns attribute to the new column value
    (*_cur_game_ptr)->score = 0; //change the previous score back to 0
    for (int i=0; i<new_rows; i++){ //iterate over rows and columns and reset grid to empty cells
        for (int j=0; j<new_cols; j++){
            (*_cur_game_ptr)->cells[i*new_cols + j] = -1;
        }
    }
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    if (cur_game->rows >= row && row >= 0 && cur_game->cols >= col && col >= 0){ //checks if the cell row and column are within bounds
        return &cur_game->cells[row*(cur_game->cols)+col]; //returns the pointer to the cell at the location
    }
    return NULL;
}


int slide_w(game * cur_game, int rows, int cols){
    int valid=0; //checks if slide was possible
    int i, j;
    for(j=0; j<cols; j++){ //for all columns
        //get first empty cell from top
        int empty=0;
        for (empty=0; empty<rows && (*get_cell(cur_game, empty, j) != -1); empty++) {
        //start at empty cell
        }
        //For every cell that could shift up
        for(i=empty+1; i<rows; i++){
            if(*get_cell(cur_game, i, j)!=-1) { //if the cell below is not empty
                *get_cell(cur_game, empty, j) = *get_cell(cur_game, i, j); //move the cell up
                valid=1; //set valid to 1
                *get_cell(cur_game, i, j) = -1;
                empty++; //increment empty
            }
        }
    }
    return valid;
}

int merge_w(game * cur_game, int rows, int cols){
    int valid=0; //checks if merge was possible
    int n, m;
    for (n=0; n<rows-1; n++){ //iterate through top of each pair
        for (m=0; m<cols; m++){ //iterate through columns
            if (*get_cell(cur_game, n, m) == -1) continue; //skip if empty cell
            if (*get_cell(cur_game, n, m) == *get_cell(cur_game, n+1, m)){ //check if cell below is the same
                *get_cell(cur_game, n, m) *= 2; //merge the cells and add their values
                cur_game->score += (*get_cell(cur_game, n, m)); //add their values to the score
                valid=1; //set valid to 1
                *get_cell(cur_game, n+1, m) = -1; //change the clel below to empty
            }
        }
    }
    return valid;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
    int rows = cur_game->rows; //initialize rows
    int cols = cur_game->cols; //initialize columns
    int valid=0; //checks if move was possible
    
    if (slide_w(cur_game, rows, cols)){ //slides the cells in the grid
        valid=1;
    }
    if (merge_w(cur_game, rows, cols)){ //merges the cells in the grid
        slide_w(cur_game, rows, cols); //if cells were merged, slide again to push cells up
        valid = 1;
    }
    return valid; //return 1 if a move was possible, 0 if not
};


int slide_s(game * cur_game, int rows, int cols){
    int valid = 0; //checks if slide is possible
    int i, j;
    for(j=0; j<cols; j++){ //for all columns
        //get first empty cell from bottom
        int empty=0;
        for (empty=rows-1; empty>=0 && (*get_cell(cur_game, empty, j) != -1); empty--) {
        //at first empty cell
        }
        //For every cell that could shift down
        for(i=empty-1; i>=0; i--){
            if(*get_cell(cur_game, i, j)!=-1) { //if the cell above is not empty
                *get_cell(cur_game, empty, j) = *get_cell(cur_game, i, j); //move the cell down
                valid = 1; //set valid to 1
                *get_cell(cur_game, i, j) = -1; //change the cell above to empty
                empty--; //decrement empty
            }
        }
    }
    return valid;
}

int merge_s(game * cur_game, int rows, int cols){
    int valid=0; //checks if merge is possible
    int n, m;
    for (n=rows-1; n>0; n--){ //iterate through top of each pair
        for (m=0; m<cols; m++){ //iterate through columns
            if (*get_cell(cur_game, n, m) == -1) continue; //skip empty cells
            if (*get_cell(cur_game, n, m) == *get_cell(cur_game, n-1, m)){ //if cell above is the same
                *get_cell(cur_game, n, m) *= 2; //merge values to the cell
                cur_game->score += (*get_cell(cur_game, n, m)); //add their values to the score
                valid = 1;
                *get_cell(cur_game, n-1, m) = -1; //change cell above to empty
            }
        }
    }
    return valid;
}


int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int valid=0;
    
    if (slide_s(cur_game, rows, cols)){ //slides cells down
        valid=1;
    }
    if (merge_s(cur_game, rows, cols)){ //merges cells
        slide_s(cur_game, rows, cols); //if cells merge, slide cells again to push cells down
        valid = 1;
    }
    return valid; //return 1 if a move was possible, 0 if not
};


int slide_a(game * cur_game, int rows, int cols){
    int valid=0; //checks if slide is possible
    int i, j;
    for (i=0; i<rows; i++){ //for all rows
        int empty=0; //get first empty cell
        for (empty=0; empty<cols && (*get_cell(cur_game, i, empty) != -1); empty++){
        //at first empty cell
        }
        //For every cell that could shift left
        for (j=empty+1; j<cols; j++){
            if(*get_cell(cur_game, i, j)!=-1) {
                *get_cell(cur_game, i, empty) = *get_cell(cur_game, i, j); //shift cell on right left
                valid = 1; //change valid to 1
                *get_cell(cur_game, i, j) = -1; //change previous cell position to empty
                empty++; //increment empty
            }
        }
    }
    return valid; 
}

int merge_a(game * cur_game, int rows, int cols){
    int valid=0; //checks if merge is possible
    int n, m;
    for (m=0; m<cols-1; m++){ //iterate through each pair of columns
        for (n=0; n<rows; n++){ //iterate through rows
            if (*get_cell(cur_game, n, m) == -1) continue; //skip empty cells
            if (*get_cell(cur_game, n, m) == *get_cell(cur_game, n, m+1)){ //if cell on right is the same
                *get_cell(cur_game, n, m) *= 2; //merge the cells together
                cur_game->score += (*get_cell(cur_game, n, m)); //add their values to score
                valid = 1; //change valid to 1
                *get_cell(cur_game, n, m+1) = -1; //change previous cell on right to empty
            }
        }
    }
    return valid;
}

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int valid=0;
    
    if (slide_a(cur_game, rows, cols)){ //slide cells left
        valid=1;
    }
    if (merge_a(cur_game, rows, cols)){ //merge cells left
        slide_a(cur_game, rows, cols); //if cells merged, slide again so that all non-empty cells are pushed left
        valid = 1;
    }
    return valid; //return 1 if a move was possible, 0 if not
};

int slide_d(game * cur_game, int rows, int cols){
    int valid=0; //checks if slide is possible
    int i, j;
    for (i=0; i<rows; i++){ //for all rows
        int empty=cols-1; //get first empty cell
        for (empty=cols-1; empty>=0 && (*get_cell(cur_game, i, empty) != -1); empty--){
        
        }
        //For every cell that could shift right
        for (j=empty-1; j>=0; j--){
            if(*get_cell(cur_game, i, j)!=-1) {
                *get_cell(cur_game, i, empty) = *get_cell(cur_game, i, j); //shift cell on left to right
                valid = 1; //change valid to 1
                *get_cell(cur_game, i, j) = -1; //change previous cell on left to empty
                empty--; //increment empty
            }
        }
    }
    return valid;
}

int merge_d(game * cur_game, int rows, int cols){
    int valid=0; //checks if merge is possible
    int n, m;
    for (m=cols-1; m>0; m--){ //iterate through each pair of columns
        for (n=0; n<rows; n++){ //iterate through rows
            if (*get_cell(cur_game, n, m) == -1) continue; //skip empty cells
            if (*get_cell(cur_game, n, m) == *get_cell(cur_game, n, m-1)){ //if cell on left is the same
                *get_cell(cur_game, n, m) *= 2; //merge their values together
                cur_game->score += (*get_cell(cur_game, n, m)); //add their values to score
                valid = 1; //set valid to 1;
                *get_cell(cur_game, n, m-1) = -1; //change previous cell to empty
            }
        }
    }
    return valid;
}

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    
    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int valid=0; //checks if move is possible
    
    if (slide_d(cur_game, rows, cols)){ //slides cells right
        valid=1;
    }
    if (merge_d(cur_game, rows, cols)){ //merges cells right
        slide_d(cur_game, rows, cols); //if merge is possible, slides again so cells are pushed right after merging
        valid = 1;
    }
    return valid; //return 1 if a move was possible, 0 if not
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int valid=0; //flag that checks if the move is valid
    for (int i=0; i<rows; i++){ //iterate over each row and column
        for (int j=0; j<cols; j++){
            if (*get_cell(cur_game, i, j) == -1){ //check if there are any empty cells
                valid = 1;
            }
            //check if any adjacent cells are the same
            if (i<rows-1 && (*get_cell(cur_game, i, j)) == (*get_cell(cur_game, i+1, j))){ //starts top and goes down for each row
                valid=1;
            }
            if (j<cols-1 && (*get_cell(cur_game, i, j)) == (*get_cell(cur_game, i, j+1))){ //starts left and goes right for each column
                valid=1;
            }
        }
    }
    return valid; //if there are any empty cells or any adjacent cells are the same, a move is possible and it returns 1. Otherwise return 0.
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
