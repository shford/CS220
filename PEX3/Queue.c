/*
 * Hampton Ford
 * Purpose: Implement a stack based on the linked list library supporting operations:
 *          init_queue(), enqueue(), dequeue(), qpeek(), display()
 *
 * Last Updated 02/28/2020
 */

#include <stdio.h>
#include "Queue.h"
#include "library.h"

/*
Usage:
    List list;
    init_queue(&list,'h');
    enqueue('t', &list);
    printf("%c", dequeue(&list));
    printf("%c", dequeue(&list));
*/

/*
 * Purpose: Make a queue based ADT
 * @Params: List* list, char data
 * @Return: void
 */
void init_queue(List* list, char data) {
    list->head = init_list(data);
    //List elements head and tail are the same for list with only 1 Node (size 1)
    list->tail = list->head;
    list->list_size = 1;
}

/*
 * Purpose: Push a char to the queue
 * @Params: List* tail, char
 * @Return: void
 */
void enqueue(List* list, char ch) {
    if (list->head == NULL) {
        printf("Queue does not exist.");
        exit(1);
    }
    list->tail = append(list->tail, ch);
    list->list_size++;
}

/*
 * Purpose: Pop a char off the queue
 * @Params: List*
 * @Return: char last pushed on string
 */
char dequeue(List* list) {
    if (list->list_size == 0) { //nothing left in list
        printf("\nQueue is empty\n");
        exit(1);
    }
    char data;
    Node* newHead;

    //Special case when one node left
    if (list->head == list->tail) {
        newHead = NULL;
    } else {
        newHead = list->head->next;
    }

    data = remNode(list->head);

    list->head = newHead;
    list->list_size--;

    return data;
}

/*
 * Purpose: Reports if queue is empty
 * @Params: List*
 * @Return: Return 0 if queue is empty
 */
int isEmptyQ(List* list) {
    if (list->list_size == 0) { //nothing left in list
        return 0;
    }
    else {
        return 1;
    }
}

/*
 * Purpose: Print queue
 * @Params: List*
 * @Return: void
 */
void q_display(List* queue) {
    list_traverse(queue->head);
}

/*
 * Purpose: Let's you see the 'top' value of the queue
 * @Params: List*
 * @Return: Return char from top of list
 */
char qpeek(List* list) {
    if (list->list_size != 0) { //list not empty
        return list->head->data;
    }
    else {
        printf("Can't peek into empty queue.");
        //exit(1);
    }
}