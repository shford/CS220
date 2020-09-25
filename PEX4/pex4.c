/*
 * Authors        :   C3C Hampton Ford and C3C Matt DeMaso
 * Last Modified  :   04/22/2020
 * Purpose        :   Create a spell checker using trees
 *
 * Final Status: Fully Functional.
 *
 * Documentation:
 *      Reading input
 *          https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm
 *          http://www.cplusplus.com/reference/cstdio/fread/
 *      Used some previous code from PEX3 to get splitstr working
 *      Used website below to brush up on strtok() from string.h
 *          https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
 *      PEX1 modified code for command line arguments
 *      PEX1 CountWordsInFile() used to get number of words in file
 *     Copied a test case from:
 *          https://www.reddit.com/r/PrequelMemes/comments/5q3du8/did_you_ever_hear_the_tragedy_of_darth_plagueis/
 *     Stripped punctuation using:
 *          https://www.browserling.com/tools/remove-punctuation
 *     Further formatted using:
 *          https://onlinestringtools.com/split-string
 *      EI with Col. Sarmiento clarifying behavior of three strings with shared roots ("hit","hip","him")
 *      EI with Col. Chiaramonte discussing PEX4 and clarifying on how C releases memory
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pex4.h"
#include "ternary_tree_lib.h"

  /*
   * Purpose: Read text from files and spellcheck all words in testFile
   * @Params: int argc, char* argv[]
   * @Return: 0 on success
   */
int main(int argc, char* argv[]) {
    //Function arguments
    if (argc != 3) //enforce number of parameters
    {
        printf("Please provide a dictionary and a file to test.\n\n");
        printf("USAGE:  CS220.exe dictionary.txt testfile.txt\n");
        return -1;
    }

    //Declarations
    char* dict; //dictionary file name
    char* testFile; //test file name
    char** dict_words;
    char** test_words;
    Tree tree;

    //Initialize Variables
    dict = argv[1];
    testFile = argv[2];
    dict_words = NULL;
    test_words = NULL;
    tree.root = NULL;
    tree.current_Node = NULL;

    //Allocate memory for words
    int dict_cnt = allocateMem(&dict_words, dict); int test_cnt = allocateMem(&test_words, testFile);

    //Read Text From Files
    printf("Reading Files...\n");
    getBuff(&dict); getBuff(&testFile);

    //Split strings
    splitstr(dict, dict_cnt, dict_words);
    splitstr(testFile, test_cnt, test_words);

    //Construct Spell Check Tree from word_list
    printf("Constructing Tree...\n");
    constructTreeDict(dict_words, dict_cnt, &tree);

    //Compare Word with Input
    printf("Checking Words...\n");
    spellCheck(test_words, test_cnt, &tree);

    //Erase all formatted words
    freeMem(&dict_words, dict_cnt); freeMem(&test_words, test_cnt);
    //Erase tree
    printf("\nDeleting Tree...\n");
    freeTree(&tree);
    return 0;
}

/*
 * Purpose: Allocate memory for an "array of words"
 *              -really a single array of pointers to char* (words), not be confused w/ a proper 2D array
 * @Params: char*** to a list of words, char* to a filename
 * @Return: int number of words read into the second parameter
 *
 * Status: DONE
 */
int allocateMem(char*** list_words, char* filename) {
    int num_words = countWordsInFile(filename);
    *list_words = calloc(num_words, sizeof(char*));
    if (*list_words == NULL) {
        printf("Failed char* allocating memory\n");
        exit(-1);
    }
    else {
        for (int i = 0; i < num_words; ++i) {
            (*list_words)[i] = calloc(sizeof(char), MAX_WORD_LENGTH);
            if ((*list_words)[i] == NULL) {
                printf("Failed word allocating memory\n");
                exit(-1);
            }
        }
    }
    return num_words;
}

/*
 * Purpose: Free all memory allocated in allocateMem()
 * @Params: char*** list_words, int num_words
 * @Return: void
 *
 * Status: DONE
 */
void freeMem(char*** list_words, int num_words) {
    for (int i = 0; i < num_words; ++i) {
        free((*list_words)[i]);
    }
    free(*list_words);
}

/*
 * Purpose: Read all data from appropriate files
 * @Params: char** filename
 * @Return: void
 *
 * Status: DONE
 */
void getBuff(char** filename) {
    //Open file
    FILE* fd = fopen(*filename, "r");
    if (fd == NULL) {
        printf("Failed opening file.\n");
        exit(FAILURE);
    }
    //Get length
    fseek(fd, 0, SEEK_END);
    int size = (int)ftell(fd);
    rewind(fd);
    *filename = calloc(size, 1); //w/out this fread throws a memory error
    if (*filename == NULL) {
        printf("Failed to allocate buffer memory");
        exit(FAILURE);
    }
    //Read file
    fread(*filename, 1, size, fd);
    fclose(fd);
}

/*
 * Purpose: Convert our data from 1D single string to 2D strings of word split along newline delimeters
 * @Params: char* unformatted word list, int num_words, char** list to format
 * @Return: void
 *
 * Status: DONE
 */
void splitstr(char* unsplitStr, int num_words, char** splitStr) {
    char* result = NULL;
    char delim[] = "\r\n";

    for (int i = 0; i < num_words; ++i) {
        result = strtok(unsplitStr, delim);
        unsplitStr = NULL;
        strcpy(splitStr[i], result);
    }
}

/*
 * Purpose: Pass one word at a time to library
 * @Params: char** word_list, int num_words, Tree* tree
 * @Return: void
 *
 * Status: DONE
 */
void constructTreeDict(char** word_list, int num_words, Tree* tree) {
    int word_indices[num_words];
    for (int i = 0; i < num_words; ++i) {
        word_indices[i] = i;
    }
    const int max_word_index = num_words - 1;
    int index = 0;
    int to_be_halfed = max_word_index;
    order_indices(word_indices, max_word_index, index, to_be_halfed);

    for (int i = 0; i <= max_word_index; ++i) {
        if (i == 0)
            constructTree(word_list[word_indices[i]], tree);
        else
            insertWord(word_list[word_indices[i]], tree);
    }
}

/*
 * Purpose: Print if each word in checklist is spelled correctly
 * @Params: char** word_list, int num_words, Tree* tree
 * @Return: void
 *
 * Status: DONE
 */
void spellCheck(char** word_list, int num_words, Tree* tree) {
    //make all letters upper-case
    for (int i = 0; i < num_words; ++i) {
        for (int j = 0; j < strlen(word_list[i]); ++j) {
            word_list[i][j] = upper_wrapper(word_list[i][j]);
        }
    }

    //check each word
    for (int i = 0; i < num_words; ++i) {
        if (checkWord(word_list[i], tree)) {
            printf("%s was spelled correctly.\n", word_list[i]);
        }
        else {
            printf("%s was spelled incorrectly, or %s is not in your dictionary.\n", word_list[i], word_list[i]);
        }
    }
}

/*
 * Purpose: Get number of words in dictionary
 * @Params: char[] filename
 * @Return: int words
 *
 * Status: DONE
 * Note: Slightly modified from PEX1
 */
int countWordsInFile(char* argFileName) {
    int wordCount = 0;

    // open the file
    FILE* filePtr = NULL;

    filePtr = fopen(argFileName, "r");
    if (filePtr == NULL) {
        printf("Error opening file.\n");
        exit(FAILURE);
    }
    else {
        // read in one word at at time and
        char charBuffer[MAX_WORD_LENGTH]; //max length of a single word

        while (fscanf(filePtr, "%s", charBuffer) == 1)
        {
            // increment the counter
            wordCount++;
        }
        //close only if filePtr is not NULL
        fclose(filePtr);
    }
    return wordCount;
}

/*
 * Purpose: Report if a number is in an array
 * @Params: const int arr[], int max_index, int curr_num
 * @Return: bool: true if the number is in our array
 *
 * Status: DONE
 */
bool isInArray(const int arr[], int max_index, int curr_num) {
    for (int i = 0; i <= max_index; ++i) {
        if (curr_num == arr[i]) {
            return true;
        }
    }
    return false;
}

/*
 * Purpose: Make an array of indices to order each word passed into tree for an pre-initialized array
 * @Params: int indices[], int max_index, int index, int to_be_halved
 * @Return: void
 *
 * Note: Works w/ a to_be_halfed >= 2, otherwise it leaves the list sequential array it's given which is fine
 * Status: DONE
 */
void order_indices(int indices[], const int max_index, int index, int to_be_halfed) {
    to_be_halfed = to_be_halfed / 2;
    bool inArr = false;
    if (to_be_halfed != 0) { //stop at index 0
        int multiplier = 1;
        int multiple = to_be_halfed * multiplier;
        while (multiple <= max_index) { //get all multiples
            if (!isInArray(indices, max_index, multiple)) { //add that number to our list
                indices[index] = multiple;
                ++index;
                ++multiplier;
            }
            else { //skip that number-we already added it
                ++multiplier;
            }
            multiple = to_be_halfed * multiplier;
        }
        order_indices(indices, max_index, index, to_be_halfed);
    }
}