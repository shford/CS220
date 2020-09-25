//
// Created by C22Steven.Ford on 3/24/2020.
//
#include <math.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include "postfix_math_lib.h"
#include "PEX3.h"
//legacy import hua #include "Stack.h"
#include "Queue.h"

#define ZERO_DIVISOR 20

void strrev(char strFrag[]);


/*
 * Purpose: Converts chars to ints
 * @Params: char
 * @Return: double
 */
double cTon(char ch) {
    if (ch == '0') {
        return 0;
    }
    if (ch == '1') {
        return 1;
    }
    if (ch == '2') {
        return 2;
    }
    if (ch == '3') {
        return 3;
    }
    if (ch == '4') {
        return 4;
    }
    if (ch == '5') {
        return 5;
    }
    if (ch == '6') {
        return 6;
    }
    if (ch == '7') {
        return 7;
    }
    if (ch == '8') {
        return 8;
    }
    if (ch == '9') {
        return 9;
    }
    return 999999; //won't reach here
}

/*
 * Purpose: Updates char for first run, num1, num2, and numbers incrementer (c)
 * @Params: const double [], double*, double*, int*, char*
 * @Return: void
 *
 * **Now legacy function
 */
/*void doFirstRun(const double numbers[], double* num1, double* num2, int* ni, char* isFirstRun) {
    *num1 = numbers[*ni]; //update num1
    --*ni; //update increment
    *num2 = numbers[*ni]; //update num2
    --*ni; //update increment
    *isFirstRun = 'f'; //update char first run
}*/

/*
 * Purpose: Returns true if is a char is an operator
 * @Params: char
 * @Return: 0 if operator else return 1
 */
int isOperator(char ch) {
    if (ch == '^' || ch == '*' || ch == '/' || ch == '+' || ch == '-') {
        return 0;
    }
    else {
        return 1;
    }
}

/*
 * Purpose: Evaluates expression
 * @Params: List* Queue, char postfix_equation to update
 * @Return: Double expression
 *
 * Note* Has handled every expression I've given it aside from variable overflow (if calculations get really crazy)
 *       including:
 *          5+2*(9-3)*6
 *          6^3+5*40...nice
 *          and many other values
 *          5*(3 1/2)*9-100
 *          5*(7/2)*9-100
 *          52.5
 *
 */
double evaluate(List *qlist, char postfix_equation[EQUATION_LEN], char* unary_op) {
    List lst;
    init_queue(&lst, '\n');

//legacy    double numbers[EQUATION_LEN];
//legacy    int n = 0; //increment for numbers and number of numbers

    char strFrag[MAX_PLACE_VALUE]; //collect numbers > 1 digit to pass to strtod()
    int f = 0; //strFrag index

    int i = 0; //postfix_equation index
    while (isEmptyQ(qlist) != 0) {
        char tmpch = dequeue(qlist);
        //do nothing on newline
        if (tmpch != '\n') {
            //update postfix_equation
            if (isdigit(tmpch) != 0 || isOperator(tmpch) == 0) { //is a number or an operator
                postfix_equation[i] = tmpch;
                ++i;
            }
            //append strFrag
            if (isdigit(tmpch) != 0) { //is a number
                strFrag[f] = tmpch;
                ++f;
            }
            if (isOperator(tmpch) == 0) { //push if is operator
                enqueue(&lst, tmpch);
            }
            //reset strFrag index and append converted (double) strFrag to numbers[]
            if (tmpch == ' ') { //testing for a null terminator won't help because our queue is NOT null terminated
                strFrag[f] = '\0'; //null terminate string for strtod()
                f = 0;

                char **requiredParam = NULL;
//legacy                numbers[n] = strtod(strFrag, requiredParam);
//legacy                ++n;

                postfix_equation[i] = tmpch; //keep spaces in postfix_equation for pretty output
                ++i;
            }
        }
    }
    postfix_equation[i] = '\0'; //append null terminator for printf()

    char tmp_postfix_eq[2*EQUATION_LEN];
    strcpy(tmp_postfix_eq, postfix_equation);

    double accumulator = 0;

    double num1 = 0;
    double num2 = 0;
    //legacy code int ni = n-1; //should decrement from n to 0 to go through every number in numbers[] in reverse order

    //new code with string
    //based off true assumption that the last non-null-terminator char will always be an operator at index strlen-1
    //char strFrag[MAX_PLACE_VALUE]; add when below code is working
    char firstrun = 't';
    for (int s = 0; s < strlen(tmp_postfix_eq); ++s) { //last ch is certainly the last operator
        char operator = tmp_postfix_eq[s];
        if (isOperator(operator) == 0) { //then we want to firstrun or find previous number
            tmp_postfix_eq[s] = '\n'; //overwrite this operator so we can more past this index next loop through
            if (firstrun == 't') {
                //get num1
                f = 0;
                char digit_found = 'f'; //used for extra space parsing
                int i = s-1; //declaring i here is actually more efficient b/c each search loop leaves off where the last one was
                for (; i >= 0; --i) { //don't want to dip below index of string //should catch 5
                    char ch = tmp_postfix_eq[i];

                    if (isdigit(ch)) {
                        strFrag[f] = ch;
                        ++f;
                        //replace that char with a newline so that we don't recopy in the next scope loop or outer loop
                        tmp_postfix_eq[i] = '\n'; //DONT USE ch HERE

                        digit_found = 't'; //can't be spaces inside a number but there can be b/w number and operator
                        //ie given: ...55 + or ...5589  + ;we can now parse that space(s) without issue
                    }
                    if ( (i == 0 || ch == ' ') && (digit_found == 't') ) { //ignore any spaces preceding operater but after digit
                        tmp_postfix_eq[i] = '\n';
                        strFrag[f] = '\0';
                        char **requiredParam = NULL;
                        num1 = strtod(strFrag, requiredParam);
                        //we've found this strFrag so our first run is over
                        firstrun = 'f';
                        break;
                    }
                    else if (ch == ' ' && digit_found == 'f') { //just discard space
                        tmp_postfix_eq[i] = '\n';
                    }
                }
                //get num2
                f = 0;
                digit_found = 'f';
                for (i-=1; i >= 0; --i) {
                    char ch = tmp_postfix_eq[i];

                    if (isdigit(ch)) {
                        strFrag[f] = ch;
                        //replace that char with a newline so that we don't recopy in the next scope loop or outer loop
                        tmp_postfix_eq[i] = '\n';
                        ++f;

                        digit_found = 't'; //can't be spaces inside a number but there can be b/w number and operator
                        //ie given: ...55 + or ...5589  + ;we can now parse that space(s) without issue
                    }
                    if ( ((i == 0) || (ch == ' ')) && (digit_found == 't')) { //ignore any spaces preceding operater but after digit
                        tmp_postfix_eq[i] = '\n';
                        strFrag[f] = '\0';
                        char **requiredParam = NULL;
                        num2 = strtod(strFrag, requiredParam);
                        //strFrag found
                        break;
                    }
                    else if (ch == ' ' && digit_found == 'f') { //just discard space
                        tmp_postfix_eq[i] = '\n';
                    }
                }

                if (operator == '^') {
                    accumulator = pow(num2, num1);
                } else if (operator == '*') {
                    accumulator = num2 * num1;
                } else if (operator == '/') {
                    if (num1 == 0) {
                        printf("Can't divide by zero.\nExiting program.\n");
                        exit(ZERO_DIVISOR);
                    }
                    accumulator = num2 / num1;
                } else if (operator == '+') {
                    accumulator = num2 + num1;
                } else if (operator == '-') {
                    accumulator = num2 - num1;
                } else { //hopefully just extra whitespace and a correct answer if we've reached this point
                }
            }
            else {
                //get num2
                f = 0;
                char digit_found = 'f';
                i=s;
                for (; i >= 0; --i) {
                    char ch = tmp_postfix_eq[i];

                    if (isdigit(ch)) {
                        strFrag[f] = ch;
                        //replace that char with a newline so that we don't recopy in the next scope loop or outer loop
                        tmp_postfix_eq[i] = '\n';
                        ++f;

                        digit_found = 't'; //can't be spaces inside a number but there can be b/w number and operator
                        //ie given: ...55 + or ...5589  + ;we can now parse that space(s) without issue
                    }
                    if ( ((tmp_postfix_eq[i] == ' ' || tmp_postfix_eq[i] == '\n')) && !isdigit(tmp_postfix_eq[i-1]) && (digit_found == 't')) { //ignore any spaces preceding operator but after digit
                        tmp_postfix_eq[i] = '\n';
                        strFrag[f] = '\0';
                        strrev(strFrag); //reverse str since we're going from left to right
                        char **requiredParam = NULL;
                        num2 = strtod(strFrag, requiredParam);
                        break;
                    }
                    else if (ch == ' ' && digit_found == 'f') { //just discard space
                        tmp_postfix_eq[i] = '\n';
                    }
                }

                if (operator == '^') {
                    accumulator = pow(accumulator, num2);
                } else if (operator == '*') {
                    accumulator *= num2;
                } else if (operator == '/') {
                    if (num2 == 0) {
                        printf("Can't divide by zero.\nExiting program.\n");
                        exit(ZERO_DIVISOR);
                    }
                    accumulator /= num2;
                } else if (operator == '+') {
                    accumulator += num2;
                } else if (operator == '-') {
                    accumulator = accumulator - num2;
                } else {
                    //hopefully just extra whitespace and a correct answer if we've reached this point
                }
            }
        }
    }


    //old code with queues and stacks that generally works but for fails for very complex expressions such as:
    //5+3*(9-3)*6
    //SUBSTITUTE legacycode HERE
    if (*unary_op == 't') {
        return -1*accumulator;
    }
    else {
        return accumulator;
    }
}

/*
 * Purpose: Reverse a string
 * @Params: char*
 * @Return: void
 *
 * Thanks to https://www.programmingsimplified.com/c-program-reverse-string#reverse-string-without-function for
 * the nice starting point
 */
void strrev(char strFrag[]) {
    int end = (int)strlen(strFrag) - 1;
    char *r = calloc(sizeof(char), 2*EQUATION_LEN);
    int begin;
    for (begin = 0; begin < strlen(strFrag); ++begin) {
        r[begin] = strFrag[end];
        --end;
    }
    r[begin] = '\0';
    strcpy(strFrag, r);
}

/*
void legacy_code() {
    char bool = 't';
    for (int o = 0; o < lst.list_size + 2; ++o) {
        char operator = dequeue(&lst);
        if (operator == '^') {
            if (bool == 't') {
                doFirstRun(numbers, &num1, &num2, &ni, &bool);
                accumulator = pow(num1, num2);
            } else {
                num2 = numbers[ni];
                --ni;
                accumulator = pow(accumulator, num2);
            }
        } else if (operator == '*') {
            if (bool == 't') {
                doFirstRun(numbers, &num1, &num2, &ni, &bool);
                accumulator = num1 * num2;
            } else {
                num2 = numbers[ni];
                --ni;
                accumulator *= num2;
            }
        } else if (operator == '/') {
            if (bool == 't') {
                doFirstRun(numbers, &num1, &num2, &ni, &bool);
                if (num2 == 0) {
                    printf("Can't divide by zero.\nIgnoring operation and continuing.\n");
                    printf("Try again.\n");
                    exit(INF);
                }
                accumulator = num1 / num2;
            } else {
                num2 = numbers[ni]; //todo if error on division check if this should be placed further down
                --ni;
                if (num2 == 0) {
                    printf("Can't divide by zero.\nIgnoring operation and continuing.\n");
                }
                accumulator /= num2;
            }
        } else if (operator == '+') {
            if (bool == 't') {
                doFirstRun(numbers, &num1, &num2, &ni, &bool);
                accumulator = num1 + num2;
            } else {
                num2 = numbers[ni];
                --ni;
                accumulator += num2;
            }
        } else if (operator == '-') {
            if (bool == 't') {
                doFirstRun(numbers, &num1, &num2, &ni, &bool);
                accumulator = num1 - num2;
            } else {
                num2 = numbers[ni];
                --ni;
                accumulator -= num2;
            }
        } else {
//hopefully just extra whitespace and a correct answer if we've reached this point
        }
    }
}*/
