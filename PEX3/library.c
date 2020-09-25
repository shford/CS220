/*
 * Hampton Ford
 * Purpose: Implement a linked list library supporting operations:
 *      init_list(), append(), remNode(), list_traverse(), list_rev_traverse()
 * Last Updated 02/23/2020
 */

#include "library.h"
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1
#define MALLOC_FAILURE -2

/*
 * Purpose: Allocate the first node in a list
 * @Params: char to assign to .data element
 * @Return: Return a pointer to new Node (error check in main)
*/
Node* init_list(char dat) {
    Node* list_start = malloc(sizeof(Node));
    if (list_start == NULL) {
        printf("Malloc failure in init_list.");
        exit(MALLOC_FAILURE);
    }
    //initialize all elements of type node
    list_start->data = dat;
    list_start->next = NULL;
    list_start->prev = NULL;

    return list_start;
}

/*
 * Purpose: Add another node to the 'end' of the list
* @Params: Node*, char
* @Return: Address to new node
*/
Node* append(Node* last_Node, char newData) {
    //create a new node
    Node *newNode = malloc(sizeof(Node));
    //handle malloc failure
    if (newNode == NULL) {
        printf("Malloc failure in append.");
        exit(MALLOC_FAILURE); //failed malloc
    }
    //Assign all elements of newNode
    newNode->data = newData;
    newNode->next = NULL;
    newNode->prev = last_Node;

    //set next element of last_Node
    last_Node->next = newNode;

    return newNode;
}

/*
 * Purpose: Remove a node from the given list
 * @Params: Node* tail or head element of List to remove
 * @Return: char data
*/
char remNode(Node* end_Node) { //end_Node is head or tail
    char dat;
    //Ensure *current* node exists
    if (end_Node == NULL) {
        printf("Empty list in remNode.");
        exit(FAILURE);
    }
    else {
        dat = end_Node->data;
         //Handle middle node
         //Shouldn't happen if using lib for only stacks and queues
        if (end_Node->prev != NULL && end_Node->next != NULL) {
            //Assign next node 'prev' element to current del_Node's 'prev' element
            end_Node->next->prev = end_Node->prev;
            //Assign prev node 'next' element to current del_Node's 'next' element
            end_Node->prev->next = end_Node->next;
            //*isEmpty = 0; //not empty
        }
        //Handle if next node exists and the prev node has not been declared yet
        //Should only run from pop() in Stack.c
        else if (end_Node->next != NULL && end_Node->prev == NULL) {
            //Assign next node 'prev' element to NULL
            end_Node->next->prev = NULL;
            //*isEmpty = 0; //not empty
        }
        //Handle if previous node exists and the next node has not been declared yet
        //Should only run from dequeue() in Queue.c
        else if (end_Node->prev != NULL && end_Node->next == NULL) {
            //Assign prev node 'next' element to NULL
            end_Node->prev->next = NULL;
            //*isEmpty = 0;
        }
        //Handle if NEITHER next node or previous Node exists
        //Should set char to data in current Node and return NULL
        else {
            //*isEmpty = 1;
        }
        //delete current node regardless of if last was declared
        free(end_Node);
    }
    return dat;
}

/*
 * Purpose: Print all values in list in order
 * @Params: Node* list_head
 * @Return: Return 0 on success and -1 on failure
*/
int list_traverse(Node* list_head) {
    if (list_head == NULL) {
        printf("Cannot traverse empty list.\n");
        return FAILURE;
    }
    Node* toss_head = list_head;
    while (toss_head != NULL) {
        //print current data val
        printf("%c", toss_head->data);
        //increment position in list
        toss_head = toss_head->next;
    }
    return 0;
}

/*
 * Purpose: Print all values in list in reverse order
 * @Params: Node* list_tail
 * @Return: Return 0 on success and -1 on failure
*/
int list_rev_traverse(Node* list_tail) {
    if (list_tail == NULL) {
        printf("Cannot traverse empty list.\n");
        return FAILURE;
    }
    Node* toss_tail = list_tail;
    while (toss_tail != NULL) {
        //print current data val
        printf("%c", toss_tail->data);
        //increment position in list
        toss_tail = toss_tail->next;
    }
    return 0;
}