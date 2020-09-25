//
// Created by C22Steven.Ford on 4/22/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ternary_tree_lib.h"


/*
 * Purpose: Allocate and initialize new nodes
 * @Params: none
 * @Return: Node* new_node
 *
 * Status: DONE
 */
Node* node_constructor() {
    Node* new_node = calloc(sizeof(Node), 1);
    new_node->data = '-';
    new_node->l_child = NULL;
    new_node->m_child = NULL;
    new_node->r_child = NULL;
    new_node->prev = NULL;

    return new_node;
}

/*
 * Purpose: Construct a tree from our dict
 * @Params: char* word, Tree* tree
 * @Return: void
 *
 * Status: DONE
 */
void constructTree(char* word, Tree* tree) {
    tree->root = node_constructor();
    tree->current_Node = tree->root;

    insertWord(word, tree);
}

/*
 * Purpose: Add one word at a time to our tree (handles duplicates also)
 * @Params: char* word, Tree* tree
 * @Return: void
 *
 * Status: DONE
 */
void insertWord(char* word, Tree* tree) {
    //Check constructTree() was called
    if (tree->root == NULL && tree->current_Node == NULL) {
        printf("Call constructTree() first.\n");
        exit(FAILURE);
    }

    //reset current_Node to root for each new word insertion
    tree->current_Node = tree->root;

    int i = 0;
    char ch;
    //Initialize tree for root node
    if (tree->current_Node->data == '-' && tree->current_Node->prev == NULL) {
        ch = upper_wrapper(word[i]);
        tree->current_Node->data = ch;
        i = 1;
    }

    //deal w/ character insertions
    for (; i <= strlen(word); ++i) { // use: <= to include newline character
        ch = upper_wrapper(word[i]);


        if (tree->current_Node->data == '-') {
            tree->current_Node->data = ch;
            continue;
        }
        //Insert straight down if m_child is NULL
        if (tree->current_Node->m_child == NULL && tree->current_Node->data != '\0') {
            tree->current_Node->m_child = node_constructor();

            tree->current_Node->m_child->data = ch;
            tree->current_Node->m_child->prev = tree->current_Node;
            //move to next next node and next letter
            tree->current_Node = tree->current_Node->m_child;
            continue;
        }
        else {
            //Next middle node exists, the current letters match
            if (tree->current_Node->data == ch && ch != '\0') {
                //move to next node and next letter
                tree->current_Node = tree->current_Node->m_child; //this line is fine from our initial loop condition
                continue;
            }
            else {
                if (ch < tree->current_Node->data) {
                    if (tree->current_Node->l_child == NULL) {
                        tree->current_Node->l_child = node_constructor();

                        tree->current_Node->l_child->data = ch;
                        tree->current_Node->l_child->prev = tree->current_Node;
                        //move to next next node and next letter
                        tree->current_Node = tree->current_Node->l_child;
                        continue;
                    }
                    else {
                        //if the right node already exists then move to it but don't increment our ch
                        //b/c we want to compare our ch to the left node. This makes it sort of recursive.
                        //move to next node but same letter
                        --i; //undo increment from our current "for loop"
                        tree->current_Node = tree->current_Node->l_child;
                        continue;
                    }
                }
                if (ch > tree->current_Node->data) { //CANNOT BE SIMPLIFIED TO ELSE{} statement-duplicate '\0' issue
                    if (tree->current_Node->r_child == NULL) {
                        tree->current_Node->r_child = node_constructor();

                        tree->current_Node->r_child->data = ch;
                        tree->current_Node->r_child->prev = tree->current_Node;
                        //move to next next node and next letter
                        tree->current_Node = tree->current_Node->r_child;
                        continue;
                    }
                    else {
                        //if the right node already exists then move to it but don't increment our ch
                        //b/c we want to compare our ch to the right node. This makes it sort of recursive.
                        //move to next node but same letter
                        --i; //undo increment from our current "for loop"
                        tree->current_Node = tree->current_Node->r_child;
                        continue;
                    }
                }
            }
        }
    }
}

/*
 * Purpose: Delete all memory allocated for a Tree
 * @Params: Tree* tree
 * @Return: void
 *
 * Status: DONE
 */
void freeTree(Tree* tree) {
    //when our root is NULL then our entire tree has been erased and we exit nicely
    if (tree->current_Node == tree->root && tree->current_Node->l_child == NULL &&
    tree->current_Node->m_child == NULL && tree->current_Node->r_child == NULL) {
        free(tree->current_Node);
        tree->root = NULL;
        tree->current_Node = NULL;
        printf("Tree Deleted.\n");
    }
    else {
        if (tree->current_Node->l_child != NULL) {
            //move to the left
            tree->current_Node = tree->current_Node->l_child;
            freeTree(tree);
        }
        else if (tree->current_Node->m_child != NULL) {
            tree->current_Node = tree->current_Node->m_child;
            freeTree(tree);
        }
        else if (tree->current_Node->r_child != NULL) {
            tree->current_Node = tree->current_Node->r_child;
            freeTree(tree);
        }
        else { //We've found a leaf at our current_node
            Node* set_child_null = NULL;
            Node* tmp_parent_ptr = tree->current_Node->prev;
            if (tree->current_Node->prev->l_child == tree->current_Node) {
                set_child_null = tree->current_Node;
                tree->current_Node->prev->l_child = NULL;
            }
            if (tree->current_Node->prev->m_child == tree->current_Node) {
                set_child_null = tree->current_Node;
                tree->current_Node->prev->m_child = NULL;
            }
            if (tree->current_Node->prev->r_child == tree->current_Node) {
                set_child_null = tree->current_Node;
                tree->current_Node->prev->r_child = NULL;
            }
            //free the leaf pointed to by current_node
            free(set_child_null);
            //assign current node to the leaf
            tree->current_Node = tmp_parent_ptr;
            //current_node is now the parent node of the leaf we just freed
            freeTree(tree);
        }
    }
}

/*
 * Purpose: Do spell checking for one word at a time
 * @Params: char* word, Tree* tree
 * @Return: int, 1 if in dictionary, 0 if not in dictionary
 */
int checkWord(char* word, Tree* tree) {
    //Check constructTree() was called
    if (tree->root == NULL && tree->current_Node == NULL) {
        printf("Call constructTree() first.\n");
        exit(FAILURE);
    }

    //reset current_Node to root for each new word insertion
    tree->current_Node = tree->root;

    int i = 0;

    //check each ch already in a node
    do {
        char ch = word[i];
        if (ch == tree->current_Node->data && tree->current_Node->m_child != NULL) { //if character matches node, continue down the same path
                tree->current_Node = tree->current_Node->m_child; //go down middle
                i++; //next letter in word
        }
        else if (ch < tree->current_Node->data && tree->current_Node->l_child == NULL) { //word goes to left and is not in dictionary
            return 0;
        }

        else if (ch > tree-> current_Node->data && tree->current_Node->r_child == NULL){ // word goes to right and is not in dictionary
            return 0;
        }
        else if (ch == tree->current_Node->data && ch == '\0') { //if current_node->data has a null character and word is over, word is completely checked
            return 1;
        }
        else if (ch < tree->current_Node->data) { //if character less than node, go down left branch
            tree->current_Node = tree->current_Node->l_child; //go down left branch, do not go to next letter in word
        }

        else if (ch > tree->current_Node->data) { //if character greater than node, go down right brach
            tree->current_Node = tree->current_Node->r_child; //go down right path, do not go to next letter in word
        }

    } while (i <= strlen(word));

    return '0'; //returns 0 if word does not match
}

/*
 * Purpose: Convert to uppercase and filter input
 * @Params: ch (word[i])
 * @Return: ch (now uppercase)
 *
 * Status: DONE
 */
char upper_wrapper(char ch) {
    if (ch != '\0') { //everything except null terminators should be alphabet characters
        if (isalpha(ch)) {
            ch = toupper(ch);
        } else {
            printf("%c is invalid. Enter alphabet characters.\n\n", ch);
            exit(FAILURE);
        }
    }
    return ch;
}