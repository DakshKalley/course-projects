#include <stdlib.h>
#include <stdio.h>

/*
 * MP 4: In this MP, I learned how to utilize GDB and discovered several bugs in semiprime.c
 * This program prints all the semiprimes in the range of the values inputted from a to b inclusive
 * Errors:
 *
 * The first error is in the main.c file
 * There is a semi-colon missing at the end of line 26. Prevents code from compiling
 *
 * The other errors are in the semiprime.c file
 *
 * In the is_prime() function, the return value inside the second if-condition should be 0 and the return value at the end of the statement should be 1.
 * This is because the function returns 1 if the number is not prime, and the second condition checks if the number is divisible by any other factor apart from 1 and itself
 * If true, this would not make the number a prime number, which is why the second if-condition should return 0.
 *
 * Line with "k=i%j" should be "k=i/j". "i%j" would include every number within the range since i and j will eventually equal one another before the loop ends.
 * This means that every number would be considered a semi-prime number. 
 * Changing k to "i/j" tests for semiprime, and if it is a prime it prints out the number.
 *
 * Adding "ret=1;" after printing the number makes sure the return value of the code is 1 if a semiprime exists and 0 if a semiprime does not exist.
 * Without "ret=1;", the code would always return 0 as their return value.
 *
 * Adding "break;" makes sure the code skips to the next iteration after printing a semiprime number.
 * The "break;" statement ensures that no correct semiprime numbers are printed more than once.
 */



/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        printf("%d ", i);
                        ret = 1;
                        break;
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
