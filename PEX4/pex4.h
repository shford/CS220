#pragma once

#include "ternary_tree_lib.h"

#define MAX_WORD_LENGTH 46
#define FAILURE -1

/*
 * Purpose: Allocate memory for an "array of words"
 *              -really a single array of pointers to char* (words), not be confused w/ a proper 2D array
 * @Params: char*** to a list of words, char* to a filename
 * @Return: int number of words read into the second parameter
 */
int allocateMem(char*** list_words, char* filename);

/*
 * Purpose: Free all memory allocated in allocateMem()
 * @Params: char*** list_words, int num_words
 * @Return: void
 */
void freeMem(char*** list_words, int num_words);

/*
 * Purpose: Read all data from appropriate files
 * @Params: char** filename
 * @Return: void
 */
void getBuff(char** filename);

/*
 * Purpose: Convert our data from 1D single string to 2D strings of word split along newline delimeters
 * @Params: char* unformatted word list, int num_words, char** list to format
 * @Return: void
 */
void splitstr(char* unsplitStr, int num_words, char** splitStr);

/*
 * Purpose: Pass one word at a time to library
 * @Params: char** word_list, int num_words, Tree* tree
 * @Return: void
 */
void constructTreeDict(char** dict, int num_words, Tree* tree);

/*
 * Purpose: Print if each word in checklist is spelled correctly then destroy tree
 * @Params: char** word_list, int num_words, Tree* tree
 * @Return: void
 */
void spellCheck(char** testFile_words, int testFile_wordcount, Tree* tree);

/*
 * Purpose: Get number of words in dictionary
 * @Params: char* filename
 * @Return: int words
 */
int countWordsInFile(char* argFileName);

/*
 * Purpose: Report if a number is in an array
 * @Params: const int arr[], int max_index, int curr_num
 * @Return: bool: true if the number is in our array
 */
bool isInArray(const int arr[], int max_index, int curr_num);

/*
 * Purpose: Make an array of indices to order each word passed into tree
 * @Params: int indices[], int max_index, int index, int to_be_halved
 * @Return: void
 */
void order_indices(int indices[], int max_index, int index, int to_be_halfed);