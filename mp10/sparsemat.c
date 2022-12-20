#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>


/* Intro Paragraph MP 10:
 * In this MP, I implemented a program to efficiently store sparse matrices.
 * Sparce matrices have lots of elements with values of zero. This means storing each entry would waste a lot of space.
 * By organizing a structure to only store non-zero elements, this MP saves space using data structures.
 * I implemented six functions to store these matrices:
 * In load_tuples(), I read data from an input file and created a matrix of the list of tuples type in order.
 * If there are any entries with a value of zero, I would delete the node if it existed. This allowed us to store only non-zero entries.
 * In gv_tuples(), I itereated over each node to find the node at a specific row and column. I then returned the value from that tuple
 * In order to implement set_tuples(), I followed the wiki and created a helper function called deleteNode()
 * The deleteNode() deletes a node if the value is zero. It also frees the node from memory.
 * The set_tuples() function then finds the correct location for the node in the list. If the entry exists, the new tuple
 * replaces the current tuple at the node. If the entry does not exist, the function inserts the node by appending pointers
 * I then implemented save_tuples(). This function wrote the sparse matrix to a text file in a format like the input file.
 * The save_tuples() output file has the list given in row major order and has no non-zero entries.
 * For the add_tuples() function, I followed the psuedocode on the wiki:
 * I first created a matrix C with the same as A and B. I then added the entries from matrix A to matrix C.
 * I then iterated over matrix B and added each entry to the respective entries at the same location in Matrix C.
 * This allowed me to perform addition with the two matrices and return one output matrix.
 * Finally, I created a destroy_tuples() function. This function freed memory with the given matrix by freeing each node and then freeing the matrix itself.
 */




sp_tuples * load_tuples(char* input_file)
{
    FILE* file = fopen(input_file, "r"); //open file with name from 'input_'file' and read data from file
    sp_tuples *typeMatrix = malloc(sizeof(sp_tuples)); //allocate memory for matrix

    int row; //initialize rows
    int col; //initialize columns
    fscanf(file, "%d %d", &row, &col); //get row and col input from file
    typeMatrix->m = row; //set matrix rows
    typeMatrix->n = col; //set matrix columns
    typeMatrix->nz = 0; //set # of non-zero entries in matrix to 0 initially
    typeMatrix->tuples_head = NULL; //initialize head pointer to null

    //initialize variables for row/col/value from input file
    int i;
    int j;
    double v;
    while (!feof(file)){ //While file is not empty
        fscanf(file, "%d %d %lf", &i, &j, &v); //get values from file
        set_tuples(typeMatrix, i, j, v); //sets element at row/col to value
    }

    fclose(file); //close input file
    return typeMatrix; //return matrix
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    sp_tuples_node *nodePtr = mat_t->tuples_head; //Set nodePtr as pointer to the current node
    while (nodePtr != NULL){ //iterate over nodes
        if (nodePtr->row == row && nodePtr->col == col){ //check if node is at row/col
            return nodePtr->value; //return node value if at correct node
        } else{
            nodePtr = nodePtr->next; //change current node to next node
        }
    }
    return 0; //return 0 if node not found
}

//create helper function deleteNode to be called by set_tuples;
void deleteNode(sp_tuples * mat_t, int row, int col){
    sp_tuples_node *nodePtr = mat_t->tuples_head;
    if (nodePtr == NULL){ //if Matrix is empty, return nothing
        return;
    }
    if (nodePtr->row == row && nodePtr->col == col){ //check if row and col is at head node
        free(nodePtr); //free node from memory
        mat_t->nz--; 
        mat_t->tuples_head = NULL; //delete the head pointer
        return;
    }
    while(nodePtr != NULL){ //iterate over nodes
        if (nodePtr->next == NULL){ //if node is at the tail node, stop loop
            break;
        }
        if (nodePtr->next->row == row && nodePtr->next->col == col){ //check if next node needs to be deleted
            sp_tuples_node *tempNode = nodePtr->next; //set temporary node to next node
            nodePtr->next = tempNode->next; //change next node to next node after
            free(tempNode); //free next node from memory
            mat_t->nz = mat_t->nz - 1; //decrease number of nonZero entries
            return;
        }
        nodePtr = nodePtr->next; //change current node to next node
    }
}

void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    if (value == 0){ //if value is 0, delete node from the list
        deleteNode(mat_t, row, col);
        return; //If no nodes found in list, return nothing
    }

    mat_t->nz += 1; //increment number of non_zero values since we are adding a node
    sp_tuples_node *newNodePtr = malloc(sizeof(sp_tuples_node)); //allocate memory for new node
    
    //set values for new node
    newNodePtr->row = row; 
    newNodePtr->col = col;
    newNodePtr->value = value;
    
    sp_tuples_node *nodePtr = mat_t->tuples_head; //node pointer for current node
    //check if the list is empty
    if (nodePtr == NULL){
        mat_t->tuples_head = newNodePtr; //set head pointer to the new node pointer
        newNodePtr->next = NULL; //set the next node to NULL (at tail node)
        return;
    }

    //if list is not empty, insert node at head
    if ((nodePtr->row > row || (nodePtr->row == row && nodePtr->col > col))){
        newNodePtr->next = nodePtr; //change first node to second node
        mat_t->tuples_head = newNodePtr; //set head to new node
        return;
    }
    
    while(nodePtr != NULL){ //iterate over node list
        if (nodePtr->row == row && nodePtr->col == col){ //check current node to replace value
            nodePtr->value = value;
            free(newNodePtr); //free memory of new node created
            mat_t->nz--; //decrease number of nonzero entries
            return;
        }
        
        if (nodePtr->next == NULL){ //if at tale node
            nodePtr->next = newNodePtr; //insert node at end
            newNodePtr->next = NULL; //set tail node
            return;
        }

        if (nodePtr->next->row > row || (nodePtr->next->row == row && nodePtr->next->col > col)){ //if at node in list (not at head)
            newNodePtr->next = nodePtr->next; //insert node
            nodePtr->next = newNodePtr;
            return;
        }

        nodePtr = nodePtr->next; //change to next node
    }
}


void save_tuples(char * file_name, sp_tuples * mat_t)
{
    FILE* file = fopen(file_name, "w"); //open file in writing mode

    fprintf(file, "%d %d\n", mat_t->m, mat_t->n); //print row and column dimensions from matrix dimensions
    sp_tuples_node *nodePtr = mat_t->tuples_head; //set nodePtr to head node
    int i;
    for (i=0; i<mat_t->nz; i++){ //print entries in row major order
        fprintf(file, "%d %d %lf\n", nodePtr->row, nodePtr->col, nodePtr->value); //print row/col/value
        nodePtr = nodePtr->next; //change node pointer to next node
    }
    fclose(file); //close file
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    sp_tuples *retmat = malloc(sizeof(sp_tuples)); //create matrix to hold result
    retmat->m = matA->m;
    retmat->n = matA->n;
    retmat->nz = 0;

    sp_tuples_node * nodePtr = matA->tuples_head; //node starting at head node in matrix A
    while (nodePtr != NULL){
        set_tuples(retmat, nodePtr->row, nodePtr->col, nodePtr->value); //setting entries in return matrix to entries from A
        nodePtr = nodePtr->next; //change node pointer to next node
    }

    nodePtr = matB->tuples_head; //change node to start at head node in matrix B

    while(nodePtr != NULL){
        set_tuples(retmat, nodePtr->row, nodePtr->col, gv_tuples(retmat, nodePtr->row, nodePtr->col) + nodePtr->value); //adding entries from B to entries in return matrix (Adding matrix A and matrix B)
        nodePtr = nodePtr->next; //change node pointer to next node
    }
	return retmat; //returning matrix with tuples added together
}


sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    return NULL;
}


	
void destroy_tuples(sp_tuples * mat_t){
	sp_tuples_node *nodePtr = mat_t->tuples_head; //set node pointer to head node
    sp_tuples_node *tempNode = NULL; //set temporary node
    while (nodePtr != NULL){ //iterate over nodes
        tempNode = nodePtr->next; //set temp node to next node
        free (nodePtr); //free current node
        nodePtr = tempNode; //change current node to the next node
    }
    free(mat_t); //free the memory allocated to the matrix
    return;
}  






