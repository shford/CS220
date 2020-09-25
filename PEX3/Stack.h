/*
 * Hampton Ford
 * Purpose: Implement a stack based on the linked list library supporting operations:
 *          init_stack(), push(), pop(), peek(), isEmpty()
 * Last Updated 02/28/2020
 */

#pragma once

#include "library.h"
//struct included in library.h

/*
 * Purpose: Initiate a stack based ADT
 * @Params: None
 * @Return: void

 * Note: Error handling is done library.c
 */
void init_stack(List* list, char data);

/*
 * Purpose: Push a char to the stack
 * @Params: List* tail, char
 * @Return: Void
 */
void push(List* list, char ch);

/*
 * Purpose: Pop a char off the stack
 * @Params: List*
 * @Return: char last pushed
 */
char pop(List* list);

/*
 * Purpose: Reports if stack is empty
 * @Params: List*
 * @Return: Return 0 if stack is empty. Non-zero if not-empty.
 */
int isEmptyStack(List* stack);

/*
 * Purpose: Let's you see the top value of the stack
 * @Params: List*
 * @Return: Return char from top of list
 */
char speek(List* list);

/*
 * Purpose: Print stack
 * @Params: List*
 * @Return: void
 */
void s_display(List* stack);