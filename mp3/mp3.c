/* 
 * This program in MP3 prints out a row of binomial coefficients in pascal's triangle
 * First, user input decides which row to print out (0 <= row index <= 40)
 * Next, the outer loop iterates through each digit in the row
 * Then, the code utilizes a nested for-loop to calculate the binomial coefficient
 * The formula for this binomial coefficient was provided in the MP
 * 
 * Partners: guibord2
 */


#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row;
  
  printf("Enter a row index: "); 
  scanf("%d",&row); //Gets user input for row index

  // Write your code here
  unsigned long coefficient = 1; //Initializes k value
  if (row == 0){ //Base case --> if row index is 0, the coefficient is always 1
    printf("%lu", coefficient);
  } else { //If 0 < row index <= 40
    for (int i = 0; i <= row; i++) { //First loop which iterates over each digit in the row
      for (int j = 1; j <= i; j++) { //Nested for-loop which calculates the coefficient (k value)
        	coefficient = (coefficient*(row+1-j))/j; //Binomial coefficient formula
      }
      printf("%lu ", coefficient); //Prints coefficient to console as unsigned integer
      coefficient = 1; //Resets coefficient since k value is 1 at start of row
    }
	}
  printf("\n");
  return 0;
}
