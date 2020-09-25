//
// Created by C22Steven.Ford on 3/24/2020.
//
#pragma once

#include "library.h"

#define MAX_PLACE_VALUE 20
#define INF 3 //used in postfix_math_lib.c

/*
 * Purpose: Converts chars to ints
 * @Params: char
 * @Return: double
 */
double cTon(char ch);

/*
 * Purpose: Evaluates expression
 * @Params: List* Queue, char postfix_equation to update
 * @Return: Double expression
 */
double evaluate(List*, char postfix_equation[], char* unary_op);

/*
 * Purpose: Returns true if is a char is an operator
 * @Params: char
 * @Return: 0 if operator else return 1
 */
int isOperator(char ch);