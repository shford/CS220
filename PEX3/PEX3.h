#pragma once

#define EQUATION_LEN 22 //allow for null terminator & newline that fgets apparently reads-I replace the \n w/ a null term
#define PRECISION 15
#define SUCCESS 0
#define FAILURE 1

#include "library.h"

/*
 * Purpose: Sanitize User Input According to Below Filter
 * @Params: Input string
 * @Return: 0 on success
 *
 * Note: The goal here is not prevent every possible stupid thing
 *       a user could enter. At a certain point I just leave that to them.
*/
int validate_user_input(char equation[]);

/*
 * Purpose: Convert equations from infix notation to post-fix notation
 * @Params: List*, List*, char* to equation, char*
 * @Return: void
 * Example Output: Given (3 + 5) * (7 - 2) output 3 5 + 7 2 - *
 *
 * From Wikipedia Article: https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 * "For the conversion there are two text variables (strings), the input and the output.
 * There is also a stack that holds operators not yet added to the output queue.
 */
void infix_to_RPN(List* slist, List* qlist, char postfix_equation[], char* unary_op);

/*
 * Purpose: Prioritize higher order PEMDAS operators
 * @Params: char operator
 * @Return: int representing operator precedence
 */
int opPrecedence(char ch);

/*
 * *Note to self: Run in *before* infix_to_rpn
 * Purpose: Perform string parsing to transform mixed numbers to fractional values
 * @Params: char * (infix, sanitized string)
 * @Return: void
 *
 * Note: This is input pre-rpn/postfix processing
 * -the only only way to recognize a mixed number is to find the space and then the numbers around it
 * -until operands are reached
 */
void mixed_to_fractional(char infix_equation[EQUATION_LEN]);

/*
 * Purpose: Clean up old string syntax for immediate parsing in mixed_to_fractional or eventual parsing in
 * infix_to_rpn
 * @Params: char*, int, int
 * @Return: void
 */
void mixed_string_clean(char infix_equation[EQUATION_LEN], int numerator, int denominator);

/*
 * Purpose: Convert double to fraction
 * @Params: double, int*, int*, int*
 * @Return: void
 */
void frac_to_mix(double result, int* integer, int* num, int* denom);

/*
 * Purpose: Find gcd of two numbers
 * @Params: int, int
 * @Return: int
 *
 * ****Let me be Explicit: This function is not my own, as cited above.
 * I found it at https://www.math.wustl.edu/~victor/mfmm/compaa/gcd.c on 04/16/2020 MM/DD/YEAR
 */
int gcd (int a, int b);