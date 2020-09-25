/*
 * Hampton Ford
 * Purpose: Implement a stack based on the linked list library supporting operations:
 *          init_queue(), enqueue(), dequeue()
 * Last Updated 02/28/2020
 */

#pragma once

#include "library.h"

/*
 * Purpose: Make a queue based ADT
 * @Params: List* list, char data
 * @Return: void
 */
void init_queue(List* list, char data);

/*
 * Purpose: Push a char to the queue
 * @Params: List* tail, char
 * @Return: void
 */
void enqueue(List* list, char ch);

/*
 * Purpose: Pop a char off the queue
 * @Params: List*
 * @Return: Character last pushed on string
 */
char dequeue(List* list);

/*
 * Purpose: Reports if queue is empty
 * @Params: List*
 * @Return: Return 0 if queue is empty
 */
int isEmptyQ(List* list);

/*
 * Purpose: Print queue
 * @Params: List*
 * @Return: void
 */
void q_display(List* queue);

/*
 * Purpose: Let's you see the 'top' value of the queue
 * @Params: List*
 * @Return: Return char from top of list
 */
char qpeek(List* list);