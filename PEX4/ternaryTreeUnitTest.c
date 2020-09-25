#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "pex4.h"
#include "ternary_tree_lib.h"


//================================================================================================
//SECTION 1
//================================================================================================

/*
 * Purpose: Test printing words via recursion
 * @Params: int num_words, int word_index
 * @Return: void
 */
void s1_recurse_list(int num_words, int word_index) {
    char* words[] = { "hello","there","general","kenobi" };
    if (word_index < num_words) {
        printf("Word %i: %s\n", word_index + 1, words[word_index]);
        ++word_index;
        s1_recurse_list(num_words, word_index);
    }

}

/*
 * Purpose: Report if a number is in an array
 * @Params: const int arr[], int max_index, int curr_num
 * @Return: bool: true if the number is in our array
 */
bool test_isInArray(const int arr[], int max_index, int curr_num) {
    for (int i = 0; i <= max_index; ++i) {
        if (curr_num == arr[i]) {
            return true;
        }
    }
    return false;
}

/*
 * Purpose: Make an array of indices to order each word passed into tree
 * @Params: int indices[], int max_index, int index, int to_be_halfed
 * @Return: void
 */
void s1_order_indices(int indices[], const int max_index, int index, int to_be_halfed) {
    to_be_halfed = to_be_halfed / 2;
    bool inArr = false;
    if (to_be_halfed != 0) { //stop at index 0
        int multiplier = 1;
        int multiple = to_be_halfed * multiplier;
        while (multiple <= max_index) { //get all multiples
            if (!test_isInArray(indices, max_index, multiple)) { //add that number to our list
                indices[index] = multiple;
                ++index;
                ++multiplier;
            }
            else { //skip that number-we already added it
                ++multiplier;
            }
            multiple = to_be_halfed * multiplier;
        }
        s1_order_indices(indices, max_index, index, to_be_halfed);
    }
}

//================================================================================================
//SECTION 2
//
//Test tree insertion functionality
//================================================================================================

/*
 * Purpose: Test duplicate handling
 * @Params:
 * @Return: 0 on success
 */
void s2_duplicates() {
    Tree tree;

    printf("Testing Tree Duplicates:\n");
    printf("Constructing Tree...\n");
    constructTree("word", &tree);
    printf("Inserting Words...\n");
    insertWord("word", &tree);
    insertWord("word", &tree);
    insertWord("word", &tree);
    printf("First Tree Constructed.\n");
    printf("First "); freeTree(&tree);
}

/*
 * Purpose: Handle larger trees
 * @Params: void
 * @Return: void
 */
void s2_bigger_trees() {
    Tree tree;

    printf("\nTesting large trees:\n");

    printf("Constructing Tree...\n");
    constructTree("Did", &tree);
    printf("Inserting Words...\n");
    insertWord("you", &tree);
    insertWord("ever", &tree);
    insertWord("hear", &tree);
    insertWord("the", &tree);
    insertWord("tragedy", &tree);
    insertWord("of", &tree);
    insertWord("Darth", &tree);
    insertWord("Plagueis", &tree);
    insertWord("the", &tree);
    insertWord("Wise", &tree);
    insertWord("I", &tree);
    insertWord("thought", &tree);
    insertWord("not", &tree);
    insertWord("Its", &tree);
    insertWord("not", &tree);
    insertWord("a", &tree);
    insertWord("story", &tree);
    insertWord("the", &tree);
    insertWord("Jedi", &tree);
    insertWord("would", &tree);
    insertWord("tell", &tree);
    insertWord("you", &tree);
    insertWord("Its", &tree);
    insertWord("a", &tree);
    insertWord("Sith", &tree);
    insertWord("legend", &tree);
    insertWord("Darth", &tree);
    insertWord("Plagueis", &tree);
    insertWord("was", &tree);
    insertWord("a", &tree);
    insertWord("Dark", &tree);
    insertWord("Lord", &tree);
    insertWord("of", &tree);
    insertWord("the", &tree);
    insertWord("Sith", &tree);
    insertWord("so", &tree);
    insertWord("powerful", &tree);
    insertWord("and", &tree);
    insertWord("so", &tree);
    insertWord("wise", &tree);
    insertWord("he", &tree);
    insertWord("could", &tree);
    insertWord("use", &tree);
    insertWord("the", &tree);
    insertWord("Force", &tree);
    insertWord("to", &tree);
    insertWord("influence", &tree);
    insertWord("the", &tree);
    insertWord("midichlorians", &tree);
    insertWord("to", &tree);
    insertWord("create", &tree);
    insertWord("life", &tree);
    insertWord("He", &tree);
    insertWord("had", &tree);
    insertWord("such", &tree);
    insertWord("a", &tree);
    insertWord("knowledge", &tree);
    insertWord("of", &tree);
    insertWord("the", &tree);
    insertWord("dark", &tree);
    insertWord("side", &tree);
    insertWord("that", &tree);
    insertWord("he", &tree);
    insertWord("could", &tree);
    insertWord("even", &tree);
    insertWord("keep", &tree);
    insertWord("the", &tree);
    insertWord("ones", &tree);
    insertWord("he", &tree);
    insertWord("cared", &tree);
    insertWord("about", &tree);
    insertWord("from", &tree);
    insertWord("dying", &tree);
    insertWord("The", &tree);
    insertWord("dark", &tree);
    insertWord("side", &tree);
    insertWord("of", &tree);
    insertWord("the", &tree);
    insertWord("Force", &tree);
    insertWord("is", &tree);
    insertWord("a", &tree);
    insertWord("pathway", &tree);
    insertWord("to", &tree);
    insertWord("many", &tree);
    insertWord("abilities", &tree);
    insertWord("some", &tree);
    insertWord("consider", &tree);
    insertWord("to", &tree);
    insertWord("be", &tree);
    insertWord("unnatural", &tree);
    insertWord("He", &tree);
    insertWord("became", &tree);
    insertWord("so", &tree);
    insertWord("powerful", &tree);
    insertWord("the", &tree);
    insertWord("only", &tree);
    insertWord("thing", &tree);
    insertWord("he", &tree);
    insertWord("was", &tree);
    insertWord("afraid", &tree);
    insertWord("of", &tree);
    insertWord("was", &tree);
    insertWord("losing", &tree);
    insertWord("his", &tree);
    insertWord("power", &tree);
    insertWord("which", &tree);
    insertWord("eventually", &tree);
    insertWord("of", &tree);
    insertWord("course", &tree);
    insertWord("he", &tree);
    insertWord("did", &tree);
    insertWord("Unfortunately", &tree);
    insertWord("he", &tree);
    insertWord("taught", &tree);
    insertWord("his", &tree);
    insertWord("apprentice", &tree);
    insertWord("everything", &tree);
    insertWord("he", &tree);
    insertWord("knew", &tree);
    insertWord("then", &tree);
    insertWord("his", &tree);
    insertWord("apprentice", &tree);
    insertWord("killed", &tree);
    insertWord("him", &tree);
    insertWord("in", &tree);
    insertWord("his", &tree);
    insertWord("sleep", &tree);
    insertWord("Its", &tree);
    insertWord("ironic", &tree);
    insertWord("he", &tree);
    insertWord("could", &tree);
    insertWord("save", &tree);
    insertWord("others", &tree);
    insertWord("from", &tree);
    insertWord("death", &tree);
    insertWord("but", &tree);
    insertWord("not", &tree);
    insertWord("himself", &tree);
    printf("Second Tree Constructed.\n");
    printf("Second "); freeTree(&tree);
}

//================================================================================================
//SECTION 3
//
//Test Spell Check functionality
//================================================================================================

/*
 * Purpose: Convert from lowercase to uppercase
 * @Params: none
 * @Return: void
 */
void s3_lower_to_upper() {
    printf("Testing Lower to Upper:\n");
    char word[] = "uppercase";
    printf("Original Word Is: %s\n", word);
    for (int i = 0; i < strlen(word); ++i) {
        word[i] = toupper(word[i]);
    }
    printf("Converted Word Is: %s\n", word);
}

/*
 * Purpose: Read text from files and spellcheck all words in testFile
 * @Params: none
 * @Return: 0 on success
 */
void s3_spell_check() {
    printf("\nTesting Spell Check:\n");
    //Declarations
    char* dict; //dictionary file name
    char* testFile; //test file name
    char** dict_words;
    char** test_words;
    Tree tree;

    //Initialize Variables
    dict = "C:\\Users\\C22Steven.Ford\\Downloads\\Spring 2020\\CompSci 220\\PEX4\\dictionary.txt";
    testFile = "C:\\Users\\C22Steven.Ford\\Downloads\\Spring 2020\\CompSci 220\\PEX4\\test1.txt";
    dict_words = NULL;
    test_words = NULL;
    tree.root = NULL;
    tree.current_Node = NULL;

    //Allocate memory for words
    int dict_cnt = allocateMem(&dict_words, dict); int test_cnt = allocateMem(&test_words, testFile);

    //Read Text From Files
    getBuff(&dict); getBuff(&testFile);

    //Split strings
    splitstr(dict, dict_cnt, dict_words);
    splitstr(testFile, test_cnt, test_words);

    //Construct Spell Check Tree from word_list
    constructTreeDict(dict_words, dict_cnt, &tree);

    //Compare Word with Input
    spellCheck(test_words, test_cnt, &tree);

    //Erase all formatted words
    freeMem(&dict_words, dict_cnt); freeMem(&test_words, test_cnt);
    //Erase tree
    freeTree(&tree);
}

//================================================================================================
//=================================  MAIN  =======================================================
//================================================================================================

/*
 * Purpose: Test program functionality
 * @Params: none
 * @Return: int
 *
 * Instructions: Rename this function 'int notmain()' in this file to 'int main()'
 *               Rename 'int main()' in PEX4.c to 'int notmain()'
 */
int notmain() {

    //section 1 tests
    printf("Test Section 1:\n");
    s1_recurse_list(4, 0);

    const int max_index = 7; int indices[max_index + 1]; int current_index = 0; int to_be_halfed = max_index;
    for (int i = 0; i <= max_index; ++i) {
        indices[i] = 0;
    }
    s1_order_indices(indices, max_index, current_index, to_be_halfed); //pass [0,1,...,9]

    //section 2 tests
    printf("\nTest Section 2:\n");
    s2_duplicates();
    s2_bigger_trees();

    //section 3 tests
    printf("\nTest Section 3:\n");
    s3_lower_to_upper();
    s3_spell_check();

    return 0;
}