/*
 * Hampton Ford
 * Purpose: Implement a stack based on the linked list library supporting operations:
 *          init_stack(), push(), pop(), peek(), display()
 *
 * Last Updated 03/24/2020
 */

#include <stdio.h>
#include "Stack.h"
#include "library.h"

/*
Usage:
    List list;
    init_stack(&list,'h');
    push('t', &list);
    printf("%c", pop(&list));
    printf("%c", pop(&list));
    isEmpty(list);
*/

/*
 * Purpose: Initiate a stack based ADT
 * @Params: List* list, char data
 * @Return: void
 */
void init_stack(List* list, char data) {
    list->head = init_list(data);
    //List elements head and tail are the same for list with only 1 Node (size 1)
    list->tail = list->head;
    list->list_size = 1; //initialize size to 1
}

/*
 * Purpose: Push a char to the stack
 * @Params: List tail, char
 * @Return: void
 */
void push(List* list, char ch) {
    //Error Checking: See if init_list() called first
    if (list->head == NULL) {
        printf("init_stack() not called.");
        exit(1);
    }
    list->tail = append(list->tail, ch); //point element tail to newnode --tmp ish previous tail points to nothing
    list->list_size++;
}

/*
 * Purpose: Pop a char off the stack
 * @Params: List
 * @Return: Character last pushed on string
 */
char pop(List* list) {
    if (list->list_size == 0) {
        printf("\nStack is empty in pop\n");
        exit(1);
    }

    char data;
    Node* newTail;

    //Special case when one node left: tail
    if (list->head == list->tail) {
        //list->head = NULL; will be true but it doesn't matter if we change this
        newTail = NULL;
    } else {
        newTail = list->tail->prev;
    }

    data = remNode(list->tail);

    //Update tail
    list->tail = newTail;
    list->list_size--;

    return data;
}

/*
 * Purpose: Reports if stack is empty
 * @Params: List*
 * @Return: Return 0 if stack is empty. Non-zero if not empty.
 */
int isEmptyStack(List* list) { //here list is NULL
    if (list->list_size == 0) { //stack list should element list_size should be 0
        return 0;
    }
    else { //stack is not empty
        return 1;
    }
}

/*
 * Purpose: Let's you see the top value of the stack
 * @Params: List*
 * @Return: Return char from top of list
 */
char speek(List* list) {
    if (isEmptyStack(list) != 0) { //list not empty
        return list->tail->data;
    }
    else {
        printf("Can't peek into empty stack.");
        //exit(1);
    }
}

/*
 * Purpose: Print stack
 * @Params: List*
 * @Return: void
 */
void s_display(List* list) {
    list_rev_traverse(list->tail);
}