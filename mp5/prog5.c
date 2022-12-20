/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */

/* Intro Paragraph:
 *
 * In MP5, I implemented three functions: set_seed(), start_game(), and make_guess()
 * in order to create a "code-breaking" game similar to Wordle. The user first enters a seed value
 * used to generate 4 random numbers that the user then must guess. Each number will be within the range from 1 to 8
 * and the user has 12 guesses to correctly guess the numbers in their proper order (Or they lose).
 * After each guess, the program tells the user the number of perfect and misplaced matches.
 * Perfect matches mean that the number guessed is correct and in the same location of the number in solution.
 * Misplaced matches mean that the number guessed is correct but in the wrong location compared to the number in solution.
 * The user, however, is only told the number of each, and is not told exactly which numbers are perfect or misplaced.
 *
 * In set_seed(), I implemented a function which took the user's seed input value. It then checked if the input was valid
 * and if it was, it utilized srand to set the seed. This seed value is to be used when generating random numbers.
 * If the seed input was invalid, the function would notify the user and request them to resubmit a valid seed value.
 *
 * In start_game(), I generated the 4 integers that would be used as the solution. I utilized rand's property to set 
 * the values as integers from 1 to 8. I also initialized a counter that would keep track of the number of guesses.
 * Finally, the function sets global variables for the solution numbers so I can check the solution values anywhere in my code.
 *
 * In make_guess(), I take in 4 integers from the user as their guess for the game. The function first checks if the guess entered
 * is a valid guess. If not, the function requests the user to resubmit a valid guess that is a sequence of 4 integers, each a value
 * from 1 to 8 inclusive. If the guess is valid, the function checks which numbers are a perfect or misplaced match.
 * I implemented four arrays to compare the guess with the solution. The first two are used to sort through each number in
 * the guess and the solution. This is useful when checking the location of the numbers in the order. If the location is the same
 * in each array and the value is the same, then the guess is a perfect match. If the value is the same but the location is
 * different, the match is misplaced. The other two arrays are used to keep track of which values in the solution and the guess are paired.
 * To avoid listing duplicate values as misplaced in several locations, the arrays used to track pairing make sure that the function only checks
 * The numbers which have not been paired yet. Finaly, at the end of each guess, the function will provide an output to the user.
 * This output tells the user the numbers of perfect matches as well as the number of misplaced matches.
 *
 * If the user guesses 12 times without guessing correctly, the user loses and the game ends.
 * If the user guesses correctly within 12 tries, the program will end and tell the user how many tries it took.
 *
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

//Initializing global variables
static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[])
{
    int seed; //Initialize seed variable which will hold value entered by user
    char post[2];
    if ((sscanf (seed_str, "%d%1s", &seed, post)) == 1) { //Takes in user input and checks if seed is an integer
        srand(seed); //Sets the seed using the user input
        return 1; //Returns 1 since user entered exactly one integer in the string
    } else {
        printf("set_seed: invalid seed\n");
    }
    return 0; //Returns 0 if user's input for seed is invalid
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game (int* one, int* two, int* three, int* four)
{
    //Uses the seed value to generate a solution number from 1 to 8
    *one = rand()%8 + 1; 
    *two = rand()%8 + 1;
    *three = rand()%8 + 1;
    *four = rand()%8 + 1;

    //Sets global guess counter to 1
    guess_number = 1;
    
    //Copy solution values into global solution variables
    solution1 = *one;
    solution2 = *two;
    solution3 = *three;
    solution4 = *four;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[], int* one, int* two, int* three, int* four)
{
    int w, x, y, z; //Initialize integers that will store guess values
    char post[2];
    //Check if guess input is valid
    if ((sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)) != 4){ //Input should include 4 integers
        printf("make_guess: invalid guess\n");
        return 0; //Return 0 if user guess is invalid
    }
    if ((w > 8 || w < 1) || (x > 8 || x < 1) || (y > 8 || y < 1) || (z > 8 || z < 1)){ //Guesses should be within the range 1<=guess<=8
        printf("make_guess: invalid guess\n");
        return 0;
    } 

    int perfect = 0; //Initialize number of perfect matches
    int misplaced = 0; //Initialize number of misplaced matches

    int solution[4]; //Initialize array to hold the solution values
    solution[0] = solution1;
    solution[1] = solution2;
    solution[2] = solution3;
    solution[3] = solution4;

    int guess[4]; //Initialize array to hold the guess values
    guess[0] = w;
    guess[1] = x;
    guess[2] = y;
    guess[3] = z;

    //Initialize arrays that check which numbers in guess and solution are matched
    int prg[4] = {0, 0, 0, 0}; //0 if unpaired, 1 if paired
    int prs[4] = {0, 0, 0, 0}; //0 if unpaired, 1 if paired

    //Checks for perfect matches
    for(int i=0; i<4; i++){ //Loops through each number in guess and solution at the same location
        if (guess[i] == solution[i]){ //Check if values are the same
            prg[i] = 1; //Show that the guess is now paired
            prs[i] = 1; //Show that the solution is now paired
            perfect++; //Increment number of perfect matches
        }
    }
    
    //Checks for misplaced matches
    for(int j=0; j<4; j++){ //Loops through each number in guess
        if (prg[j] == 0){ //Checks that number in guess is not paired
            for(int k=0; k<4; k++){ //Loops through each number in solution to check the guess
                if ((solution[k] == guess[j]) && (prs[k] == 0) && (prg[j] == 0)){ //If numbers are the same, make sure that neither value is already paired
                    prg[j] = 1; //Show that the guess is now paired
                    prs[k] = 1; //Show that the solution is now paired
                    misplaced++; //Increment number of misplaced matches
                }
            }
        }   
    }
    
    *one = w;
    *two = x;
    *three = y;
    *four = z;
    //Output the number of perfect and misplaced matches
    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, misplaced);
    guess_number++; //Increment the number of guesses
    return 1; //Return 1 since the user guess is valid
}


