/*
 * Created By:      Hampton Ford
 * Class/Project:   CS220 PEX3
 * Purpose:         Receive an algebraic equation in Infix Notation and output the equation in Post-Fix Notation
 * Submission:      04/16/2020
 * Documentation:
 *  Read https://en.wikipedia.org/wiki/Polish_notation  &&  https://en.wikipedia.org/wiki/Reverse_Polish_notation to
 *      understand the Notations
 *  Read https://en.wikibooks.org/wiki/C_Programming/stdio.h/getchar to understand getchar() function
 *  Used https://www.mathblog.dk/tools/infix-postfix-converter/ to divine the order of operations for postfix notation
 *  Wikipedia Article: https://en.wikipedia.org/wiki/Shunting-yard_algorithm used to understand algorithm
 *  Read usage and return values from https://www.programiz.com/c-programming/library-function/ctype.h/isdigit
 *  Discovered the beautiful strtod() c function from
 *      https://stackoverflow.com/questions/5580975/problem-with-string-conversion-to-number-strtod
 *  User: Avakar answer to struct debugging issue on Stack Overflow
 *      https://stackoverflow.com/questions/1813991/c-structure-with-pointer-to-self
 *  Realized need for isDigit() custom function that supports '.' b/c isdigit() does not from reading
 *      https://stackoverflow.com/questions/43634010/why-isdigit-return-false-on-float/43634044
 *  For converting integers to strings
 *      https://stackoverflow.com/questions/190229/where-is-the-itoa-function-in-linux
 *  Brushed up on strcat
 *      https://www.tutorialspoint.com/c_standard_library/c_function_strcat.htm
 *  Brushed up on strcpy
 *      https://www.tutorialspoint.com/c_standard_library/c_function_strcpy.htm
 *  Used below website for testing output
 *      https://www.mathblog.dk/tools/infix-postfix-converter/
 *  Learned how to use sprintf() so that was pretty productive
 *      https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
 *  Modified strrev() from
 *      https://www.programmingsimplified.com/c-program-reverse-string#reverse-string-without-function
 *  Learned how to use strtok()
 *      https://stackoverflow.com/questions/3889992/how-does-strtok-split-the-string-into-tokens-in-c
 *  Borrowed gcd function from Mladen Victor Wickerhauser although he got the algorithm from Euclid
 *      https://www.math.wustl.edu/~victor/mfmm/compaa/gcd.c on 04/16/2020 MM/DD/YEAR
 *  Recieved several EI sessions from Lt. Col. Chiaramonte who helped me
 *      1) Better understand the assignment
 *      2) Develop algorithms to solve the given problems
 *      3) Debug a few logic errors in evaluate() found in file postfix_math_lib.c
 *      4) Pointed out I needed to fix issues w/ negative numbers, so I did
 */

/*
 * Known Issues:
 *      Approximating decimals will lead to accuracy to only within 4 decimal places although it can be higher
 *          -the limitation is what strtok() will return
 *      Overflowing variable type limits in the calculator (bounds checking should be fine though) (ie int overflow etc)
 *      The calculator filter should meet project requirements but it's not perfect
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "PEX3.h"
#include "Stack.h"
#include "Queue.h"
#include "postfix_math_lib.h"

/*
 * Purpose: Receive an equation in infix notation: output post-fix notation = result of expression
 * @Params: none
 * @Return: 0 on success, -1 on failure
 */
int main(void) {
    /*
     1) get valid input
    *
    */
    printf("\nThis program receives infix notation and prints post-fix notation and accompanying result.\n\n");
    printf("Do not count on this calculator for precise calculations.\n");
    printf("Example input: 5 1/2+(4*34)*5-2+7^3\n");
    printf("Enter an Algebraic Expression Up to 20 Characters: ");
    char* infix_equation = calloc(sizeof(char), EQUATION_LEN);
    char* postfix_equation = calloc(sizeof(char), 2*EQUATION_LEN);
    List slist;
    List qlist;
    validate_user_input(infix_equation); //pass by reference
    mixed_to_fractional(infix_equation); //reaches mixed just fine
    printf("\nPrefix Expression is: %s\n", infix_equation);

    /*
     2) format input to post-fix notation
    */
    char unary_op = 'f';
    infix_to_RPN(&slist, &qlist, infix_equation, &unary_op); //pass by reference
    free(infix_equation);
    //s_display(&slist);
    //q_display(&qlist);
    /*
     3) Get result of expression
    */
    double result = evaluate(&qlist, postfix_equation, &unary_op);
    printf("Postfix expression is: %s\n", postfix_equation);
    free(postfix_equation);
    /*
      4) Print result
     */
    if ((int)result != result) {
        int integer = 0;
        int numerator = 0;
        int denominator = 0;
        frac_to_mix(result, &integer, &numerator, &denominator);
        if (integer == 0) {
            printf("Postfix evaluates to: %d/%d.\n", numerator, denominator);
        }
        else {
            printf("Postfix evaluates to: %d %d/%d.\n", integer, numerator, denominator);
        }
    }
    else {
        printf("Postfix evaluates to: %d", (int)result);
    }

    return 0;
}

/*
 * Purpose: Sanitize User Input According to Below Filter
 * @Params: Input string
 * @Return: 0 on success
 *
 * Note: The goal here is not prevent every possible stupid thing
 *       a user could enter. At a certain point I just leave that to them.
*/
int validate_user_input(char equation[EQUATION_LEN]) {
    char filter[] = " 0123456789+-*/^()";
    char doRepeat = 'f'; //assumes ALL input will be valid
    //Enforce filter to allow only [1-9]()+-*/^()
    fflush(stdin);
    fgets(equation, EQUATION_LEN, stdin); //Per POSIX man page: fgets function reads at most one less than the number of characters specified by n from the stream
    equation[strlen(equation)-1] = '\0'; //ensure final newline

    //Check that all chars are within filter
    int chrSetInd = 0;
    for (int i = 0; i < strlen(equation); ++i) {
        char ch = equation[i];
        if (chrSetInd == strlen(filter)) { //chr is not in set so break out of this loop w/ doRepeat true
            doRepeat = 't';
            break;
        }
        chrSetInd = 0; //reset for each char
        for (int j = 0; j < strlen(filter); ++j) {
            char fch = filter[j];
            if (ch == fch) {
                break; //ch is fine so continue checking
            }
            else {
                ++chrSetInd;
            }
        }
    }

    //Detect mismatched parenthesis
    int num_opening_paren = 0;
    int num_closing_paren = 0;
    for (int i = 0; i < strlen(equation); ++i) {
        if (equation[i] == '(') {
            ++num_opening_paren;
        }
        if (equation[i] == ')') {
            ++num_closing_paren;
        }
    }
    if (num_opening_paren != num_closing_paren) {
        printf("You have mismatched parenthesis.\n");
        doRepeat = 't';
    }

    //Check at least 1 operator given
    int operator_count = 0;
    for (int i = 0; i < strlen(equation); ++i) {
        if (isOperator(equation[i]) == 0) {
            ++operator_count;
            //we have at least 1 operator if this runs so we're done w/ this loop
            break;
        }
    }
    if (operator_count < 1) {
        doRepeat = 't';
    }

    //---------------------------------------------
    if (doRepeat == 't') {
        printf("Ensure valid data in the set \"' '0123456789+-*/^()\"\n");
        validate_user_input(equation);
    } else {
        return 0;
    }
    return 2;//ignore clang-tidy--can't ever not return
}

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
void infix_to_RPN(List* op_stack, List* qlist, char infix_str[EQUATION_LEN], char* unary_op) {
    //Below code was heavily modified from Wikipedia article pseudocode listed in header and Docs
    init_queue(qlist, '\n');
    init_stack(op_stack, '\n');
    *unary_op = 'f';
    if (infix_str[0] == '-') {
        //infix_str[0] = '0';
        *unary_op = 't';
    }

        int i = 0;
        if (*unary_op == 't') {
           i = i + 1; //skip unary op
        }
        for (; i < strlen(infix_str); ++i) {
        char ch = infix_str[i];

        if ( isdigit(ch) != 0 ) { //ignore clang-tidy here. This line works fine.
            enqueue(qlist, ch);
        }
        else if (isOperator(ch) == 0 && ch != '(' && ch != ')') { //properly add spaces
            enqueue(qlist, ' ');
        }
        if ( (ch == '^' || ch == '*' || ch == '/' || ch == '+' || ch == '-') && (ch != '(' || ch != ')') ) {
            while ( (opPrecedence(speek(op_stack))>=opPrecedence(ch))  && (isEmptyStack(op_stack) != 0) && (speek(op_stack) != '\n') ) {
                enqueue(qlist, pop(op_stack));
            }
            push(op_stack, ch);
        }
        if (ch == '(') {
            push(op_stack, ch);
        }
        if (ch == ')') {
            while (speek(op_stack) != '(' && (isEmptyStack(op_stack) != 0) && (speek(op_stack) != '\n')) {
                enqueue(qlist, pop(op_stack));
            }
            if (speek(op_stack) == '(') {
                pop(op_stack);
            }
        }
    }

    while ( (isEmptyStack(op_stack) != 0) && (speek(op_stack) != '\n') ) {
        enqueue(qlist, pop(op_stack));
    }
    enqueue(qlist, ' ');
}

/*
 * Purpose: Prioritize higher order PEMDAS operators
 * @Params: char operator
 * @Return: int representing operator precedence
 */
int opPrecedence(char ch) {
    if (ch=='^') {
        return 3; //highest priority for exponential operator
    }
    else if (ch=='/' || ch=='*') {
        return 2; //high priority than + or - operator
    }
    else if (ch=='+' || ch=='-') {
        return 1; //lowest priority among operators
    }
    else {
        return 0; //works for operands
    }
}

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
void mixed_to_fractional(char infix_equation[EQUATION_LEN]) {
    int whole_number = 0;
    int numerator = 0;
    int denominator = 0;
    for (int i = 0; i < strlen(infix_equation); ++i) {
        char ch = infix_equation[i];
        char did_something = 'f'; //for use in case indices don't match up on new infix_equation from mixed_string_clean

        char strFrag[MAX_PLACE_VALUE]; //collect numbers > 1 digit to pass to strtod()
        int f = 0; //strFrag index

        if (ch == ' ') {
            did_something = 't';
            infix_equation[i] = '\n'; //overwrite spaces
            //get left-most number
            for (int s = i-1; s >= 0; --s) { //left of the space there must be a number
                if (isdigit(infix_equation[s])) { //will continue until we hit an operator
                    strFrag[f] = infix_equation[s];
                    ++f;
                    infix_equation[s] = '\n';
                }
                else {
                    //b/c s>=0 condition, the whole_number assignment must be outside the loop or it won't run when
                    //the number we're storing has final digit at infix_equation[0]
                    break; //found previous operator if not digit at if not last index of str[]
                }
            }
            strFrag[f] = '\0';
            char **requiredParam1 = NULL;
            whole_number = (int)strtod(strFrag, requiredParam1);

            //get right numerator
            int a; //useful for skipping directly past '/' in getting denominator
            f = 0;
            for (a = i+1; a <= strlen(infix_equation); ++a) { //left of the space there must be a number
                if (isdigit(infix_equation[a])) { //will continue until we hit an operator
                    strFrag[f] = infix_equation[a];
                    ++f;
                    infix_equation[a] = '\n'; //overwrite number left of space
                }
                else { //in effect this else should be expecting a '/' unless the user is an idiot
                    //same issue can't apply here as in first for loop
                    strFrag[f] = '\0';
                    char **requiredParam2 = NULL;
                    numerator = (int)strtod(strFrag, requiredParam2);

                    if (infix_equation[a] == '/') {
                        infix_equation[a] = '\n'; //todo: *Note: This should overwrite the '/' for mixed_string_clean
                        break; //exit this loop to the next
                    }

                }
            }

            f = 0;
            for (a+=1; a <= strlen(infix_equation); ++a) { //todo; chek skip 1 value to the right of '/' automatically
                if (isdigit(infix_equation[a])) { //will continue until we hit an operator
                    strFrag[f] = infix_equation[a];
                    ++f;
                    infix_equation[a] = '\n'; //overwrite number left of space
                }
                else {
                    //b/c s<=strlen, the whole_number assignment must be outside the loop or it won't run when
                    //the number we're storing in strFrag has final digit at infix_equation[strlen(infi...) - 1]
                    break; //found next operator if not digit found if not at last str index
                }
            }
            strFrag[f] = '\0';
            char **requiredParam3 = NULL;
            denominator = (int)strtod(strFrag, requiredParam3);
            numerator += whole_number * denominator;
            //no op required on denominator


            //that mixed_string_clean stays in loop ensures no more than 1 '\n' cleanup at a time
            if (did_something == 't') {
                mixed_string_clean(infix_equation, numerator, denominator);
                i = 0; //reset for loop in case indices shifted back from replacement
            }
        }
    }
}

/*
 * Purpose: Clean up old string syntax for immediate parsing in mixed_to_fractional or eventual parsing in
 * infix_to_rpn
 * @Params: char*, int, int
 * @Return: void
 */
void mixed_string_clean(char infix_equation[EQUATION_LEN], int numerator, int denominator) {
    fflush(stdin);
    char *tmp_pointer = calloc(sizeof(char), EQUATION_LEN);

    char* s_numerator = calloc(sizeof(char), EQUATION_LEN);
    char* s_denominator = calloc(sizeof(char), EQUATION_LEN);
    sprintf(s_numerator, "%d" , numerator);
    sprintf(s_denominator, "%d" , denominator);

    int tmp_pointer_index = 0; //must index separately
    char first_newline_instance = 't';
    for (int i = 0; i < strlen(infix_equation); ++i) {
        char ch = infix_equation[i];
        //copy nonnewline chars to new array if not first run else run regardless. Overwrites all non-first newlines
        if (ch != '\n') { //intentionally doing nothing if for all newline > 1 except the for loop is incrementing i
            tmp_pointer[tmp_pointer_index] = infix_equation[i];
            ++tmp_pointer_index;
        }
        else {
            if (first_newline_instance == 't') { //should only once
                char* get_add_len = calloc(sizeof(char), EQUATION_LEN); //exists only for me to get len of "num/den"
                strcat(get_add_len, s_numerator);
                strcat(get_add_len, "/\0");
                strcat(get_add_len, s_denominator);

                //free s_numerator and s_denominator
                free(s_numerator);
                free(s_denominator);
                //UPDATE str indexing
                tmp_pointer_index += (int)strlen(get_add_len); //must overwrites last char on tmp_pointer (ie \0)
                strcat(tmp_pointer, get_add_len);
                //free get_add_len
                free(get_add_len);
                first_newline_instance = 'f';
            }
        }
    }
    infix_equation[tmp_pointer_index] = '\0'; //ensure new string is null-terminated
    strcpy(infix_equation, tmp_pointer); //swap old addresses had weird behavior so... strcpy it is-buffer not an issue
    free(tmp_pointer); //free old char* address - no memory leaks for us
}

/*
 * Purpose: Convert double to fraction
 * @Params: double, int*, int*, int*
 * @Return: void
 */
void frac_to_mix(double result, int* integer, int* num, int* denom) {
    char *formatting = calloc(sizeof(char), PRECISION+EQUATION_LEN); //integer and float parts
    snprintf(formatting, (PRECISION+EQUATION_LEN), "%lf", result);

    char *s_integer = calloc(sizeof(char), EQUATION_LEN);
    char* s_num = calloc(sizeof(char), PRECISION);
    //need to call strtok() twice
    char delim[] = ".";
    strcpy(s_integer, strtok(formatting, delim));
    strcpy(s_num, strtok(NULL, delim));

    free(formatting);

    //deal with denominator component
    char **neededParam = NULL;
    *denom = (int)pow(10, (int)strlen(s_num));
    //deal with numerator component
    *num = (int)strtod(s_num, neededParam);

    int gcd_val = gcd(*num, *denom);
    *num = *num / gcd_val;
    *denom = *denom / gcd_val;

    free(s_num);

    //deal with integer component
    neededParam = NULL;
    *integer = (int)strtod(s_integer, neededParam);
    // Negatives handled in postfix_math_lib.c except for one case:
    // Negative case not handled yet is if -0.85 then carry negative to numerator of fraction
    if ((s_integer[0] == '-') && (*integer == 0)) {
        *num = *num * -1;
    }
    free(s_integer);
}

/*
 * Purpose: Find gcd of two numbers
 * @Params: int, int
 * @Return: int
 *
 * ****Let me be Explicit: This function is not my own, as cited above.
 * I found it at https://www.math.wustl.edu/~victor/mfmm/compaa/gcd.c on 04/16/2020 MM/DD/YEAR
 */
int gcd ( int a, int b ) {
    int c;
    while ( a != 0 ) {
        c = a; a = b%a;  b = c;
    }
    return b;
}