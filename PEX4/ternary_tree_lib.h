#pragma once

#define FAILURE -1

//nodes
typedef struct Node_type {
    char data;
    //left, middle, and right child nodes
    struct Node_type* l_child;
    struct Node_type* m_child;
    struct Node_type* r_child;
    //previous node for when freeing
    struct Node_type* prev;
} Node;

//tree
typedef struct Tree_type {
    struct Node_type* root;
    struct Node_type* current_Node;
} Tree;


/*
 * Purpose: Construct a tree from our dict
 * @Params: char* word, Tree* tree
 * @Return: void
 */
void constructTree(char* word, Tree* tree);

/*
 * Purpose: Add one word at a time to our tree (handles duplicates also)
 * @Params: char* word, Tree* tree
 * @Return: void
 */
void insertWord(char* word, Tree* tree);

/*
 * Purpose: Delete all memory allocated for a Tree
 * @Params: Tree* tree
 * @Return: void
 */
void freeTree(Tree* tree);

/*
 * Purpose: Do spell checking for one word at a time
 * @Params: char* word, Tree* tree
 * @Return: int, 1 if in dictionary, 0 if not in dictionary
 */
int checkWord(char* word, Tree* tree);

/*
 * Purpose: Convert to uppercase and filter input
 * @Params: ch (word[i])
 * @Return: ch (now uppercase)
 */
char upper_wrapper(char ch);