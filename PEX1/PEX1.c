/** PEX1.c
 * ===========================================================
  Name: CS220, Spring 2020
 
 Second Turn-In Date: 02/02/2020
  Purpose:  Code provided for PEX 1 - Debugging a word cloud

 Docs:
Used to understand why retWordCount was unwritable https://stackoverflow.com/questions/24739986/catching-c-access-violation-writing-exception

Used to understand how to declare a pointer to a dynamically allocated array of a struct type with potentially 
dynamically allocated elements https://stackoverflow.com/questions/41091402/get-and-set-values-in-a-dynamically-allocated-array-of-structures

Used https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4703?view=vs-2019
to fix relevant compiler warning

Used https://stackoverflow.com/questions/17993591/c-access-violation-reading-location-0xcdcdcdcd-error-on-calling-a-function to understand
an uninitialized error code

Used https://stackoverflow.com/questions/25516740/run-time-check-failure-2-stack-around-the-variable-foo-was-corrupted to understand stack
corruption possible cause

Col Chiaramonte helped me debug a dynamic error I created.

C3C Grady Phillips told me to check how a string is copied so I searched around until I found
setting char* pnters equal

No other help recieved

NOTES: I fixed everything I could.
* ===========================================================
 **/
#include "PEX1.h"
#include "WordCloud.h"

 /** -------------------------------------------------------------------
  * Counts the unique words in a file.
  * @param argFileName text file to count words in
  * @return number of total words in the file
   -------------------------------------------------------------------*/
int CountWordsInFile(char* argFileName)
{
	int wordCount = 0;

	// open the file
	FILE* filePtr = NULL;

	filePtr = fopen(argFileName, "r");

	if (!(filePtr == NULL))
	{
		// read in one word at at time and
		char charBuffer[MAX_EXCLUDE_SIZE]; //actual word list is 123 + newlines && null terminators

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

/** -------------------------------------------------------------------
 * Counts the unique words in a file.
 * @param argWordCount - word count to be deleted
  -------------------------------------------------------------------*/
void DeleteWordCount(WordCount* argWordCount)
{
	for (int i = 0; i < NumUniqueWords(argWordCount); i++)
	{
		free(argWordCount[i].word);
	}

	free(argWordCount);
}

/** -------------------------------------------------------------------
 * Removes non alphas from the input word and makes it all uppercase
 * @param argWord - word to convert
 *
  -------------------------------------------------------------------*/
void RemovePunctuationMakeUpperCase(char* argWord)
{
	char* src = argWord;
	char* dst = argWord;

	while (*src)
	{
		if (!isalpha((unsigned char)* src))
		{
			/* Skip this character */
			src++;
		}
		else if (islower((unsigned char)* src))
		{
			/* Make it lowercase */
			*dst++ = toupper((unsigned char)* src);
			src++;
		}
		else if (src == dst)
		{
			/* Increment both pointers without copying */
			src++;
			dst++;
		}
		else
		{
			/* Copy character */
			*dst++ = *src++;
		}
	}

	*dst = 0;
}

/** -------------------------------------------------------------------
 * Prints the words and their frequencies
 * @param argWordCounts - array of word frequencies
 * @param argWords - array of words
   -------------------------------------------------------------------*/
void PrintWordsToConsole(WordCount* argWordCount)
{
	// print out each word and it's frequency
	for (int index = 0; argWordCount[index].word != NULL; index++)
	{
		printf("%d %s\n", argWordCount[index].count, argWordCount[index].word);
	}
}

int NumUniqueWords(WordCount* argWordCount)
{
	int i = 0;
	while (argWordCount[i].word != NULL)
	{
		i += 1; //fix infinite loop ?
	}

	return i;
}

/** -------------------------------------------------------------------
 * Allocates memory for the word list array.
 * @param argNumberOfWords number of words in the file.
 * @return array of WordCounts.
  -------------------------------------------------------------------*/

//"initialize an array of structs with the proper number of words"
//"dynamically allocate memory for an array of structs with the proper number of words"

WordCount* CreateWordCountArray(int argNumberOfWords)
{
	//pointer to WordCount structs
	WordCount* exclusionPointer = malloc((argNumberOfWords + 1) * sizeof(WordCount));
	//now we have an array of structs

	//assign ALL struct to NULL -important
	for (int i = 0; i < argNumberOfWords+1; ++i) {
		exclusionPointer[i].word = NULL;
		exclusionPointer[i].count = 0;
	}
	return exclusionPointer;
}

/** -------------------------------------------------------------------
 * Reads a file of words to exclude from the word cloud.
 * @param argFileName - text file to get exclude words from
 * @return Array containing words to exclude
   -------------------------------------------------------------------*/
WordCount* ReadExclusionFile(char* argFileName)
{
	// get the count of words
	int numWords = CountWordsInFile(argFileName) ;

	// if there are no words then return NULL
	if (numWords <= 0)
	{
		return NULL;
	}
	else
	{
		// open the file
		FILE* filePtr = NULL;

		filePtr = fopen(argFileName, "r");

		if (filePtr == NULL) {
			printf("File Pointer in Read Exclusion File is Bad");
			return NULL;
		}

		// create a buffer
		char charBuffer[MAX_EXCLUDE_SIZE];

		// initialize an array of structs with the proper number of words
		WordCount* wordCountArray = CreateWordCountArray(numWords);

		// read in each word and add it to the array if it isn't already there
		while (fscanf(filePtr, "%s", charBuffer) == 1)
		{
			RemovePunctuationMakeUpperCase(charBuffer);
			if (!WordExistsInWordCount(wordCountArray, charBuffer)) {
				UpdateWordCount(wordCountArray, charBuffer);
			}
		}

		// close the file and return
		fclose(filePtr);
		return wordCountArray;
	}

}

/** -------------------------------------------------------------------
 * Reads a file of words from story to build the word cloud.
 * @param argFileName - text file build word cloud from
 * @param argExclusionList - WordCount array with words to exclude
 * @return Map containing words and counts from story
   -------------------------------------------------------------------*/
WordCount* ReadStoryFile(char* argFileName, WordCount* argExclusionList)
{
	// get the count of words
	int numWords = CountWordsInFile(argFileName);

	// if there are no words then return NULL
	if (numWords <= 0)
	{
		return NULL;
	}
	else {
		// open the file
		FILE* filePtr = NULL;
		
		filePtr = fopen(argFileName, "r");

		if (!filePtr)
			return NULL;

		// create a buffer
		char charBuffer[MAX_WORD_LENGTH];

		// dynamically allocate memory for an array of structs with the proper number of words
		WordCount* returnWordCount = CreateWordCountArray(numWords);

		// read in each word and add it to the counted map if it isn't already there or update it's frequency
		while (fscanf(filePtr, "%s ", charBuffer) == 1)
		{
			RemovePunctuationMakeUpperCase(charBuffer);
			if (!WordExistsInWordCount(argExclusionList, charBuffer)) {
				UpdateWordCount(returnWordCount, charBuffer);
			}
		}

		// close the file and return
		fclose(filePtr);
		return returnWordCount;
	}

}

/** -------------------------------------------------------------------
 * Checks if a word is already stored in an existing WordCount
 * @param argWordCount - array to search in
 * @param argBuffer - word to look for
 * @return bool returns true/false for word existing in argWordCount
   -------------------------------------------------------------------*/
bool WordExistsInWordCount(WordCount* argWordCount, char* argBuffer)
{
	int i = 0;
	while (argWordCount[i].word != NULL)
	{
		if (strcmp(argWordCount[i].word, argBuffer) == 0)
		{
			return true;
		}

		i++;
	}
	return false;
}

/** -------------------------------------------------------------------
 * Updates count of unique words and adds word to array (argWordCount)
 * @param argWordCount - array to search in
 * @param argBuffer - word to look for
   -------------------------------------------------------------------*/
void UpdateWordCount(WordCount* argWordCount, char* argBuffer)
{
	int i = 0;
	while (argWordCount[i].word != NULL)	{ //all 32 words
		if (strcmp(argWordCount[i].word, argBuffer) == 0)
		{
			argWordCount[i].count++;
			return;
		}
		i++;
	}

	argWordCount[i].word = malloc(MAX_WORD_LENGTH * sizeof(char));
	strcpy(argWordCount[i].word, argBuffer);
	argWordCount[i].count = 1;

}

/** -------------------------------------------------------------------
 * Partitions the arrays into upper and lower portions around a pivot
 * @param argWordCounts - array of word frequencies
 * @param argWords - array of words
 * @param argLow - low index into arrays
 * @param argHigh - high index into arrays
 * @return pivot index
   -------------------------------------------------------------------*/
int QuickSortPartition(WordCount* argWordCount, int argLow, int argHigh)
{
	int midpoint = 0;
	int pivot = 0;

	int done = 0;

	// calc midpoint and pivot
	midpoint = argLow + (argHigh - argLow) / 2;
	pivot = argWordCount[midpoint].count;

	while (!done)
	{
		// move the high pointer
		while (argWordCount[argHigh].count < pivot)
		{
			argHigh--;
		}

		// move the low pointer
		while (pivot < argWordCount[argLow].count)
		{
			argLow++;
		}

		// check if the pointers have crossed
		if (argLow >= argHigh)
		{
			done = 1;
		}
		else
		{
			// swap frequency and word
			WordCount tempWordCount;

			tempWordCount = argWordCount[argLow];
			argWordCount[argLow] = argWordCount[argHigh];
			argWordCount[argHigh] = tempWordCount;

			// move pointers
			argLow++;
			argHigh--;
		}
	}

	// return the location of the pivot point
	return argHigh;
}

/** -------------------------------------------------------------------
 * Quicksorts the arrays
 * @param argWordCounts - array of word frequencies
 * @param argWords - array of words
 * @param argLow - low index into arrays
 * @param argHigh - high index into arrays
   -------------------------------------------------------------------*/
void QuickSortWords(WordCount* argWordCount, int argLow, int argHigh)
{
	// if the points haven't crossed
	if (argLow < argHigh)
	{
		// partition the arrays
		int pivot = QuickSortPartition(argWordCount, argLow, argHigh);

		// sort the partitions
		QuickSortWords(argWordCount, argLow, pivot);
		QuickSortWords(argWordCount, pivot + 1, argHigh);
	}
}

int main(int argc, char** argv)
{
	
	// check that all arguments were provided
	if (argc < 4) //program_name, text_in, exclude.txt, output
	{
		printf("Please provide a story file to read, an exclusion word list, and an filename to create.\n");
		printf("USAGE:  CS220.exe storyFile [exclusionWordFile] [outputFileName]\n");
		return -1;
	}
	printf(argv[1]);
	printf(argv[2]);
	printf(argv[3]);
	
	// create excluded words map and fill it in if the argument is provided
	WordCount* excludedWords = NULL;


	excludedWords = ReadExclusionFile(argv[2]);

	// create and fill in the story word map
	WordCount* storyWordMap = ReadStoryFile(argv[1], excludedWords);


	// dump the map into the parallel arrays
	int numUniqueWords = NumUniqueWords(storyWordMap);

	// if an output file is provided build the html word cloud
	if (argc > 3) {
		BuildWordCloud(storyWordMap, argv[3], numUniqueWords);
	}

	// sort the words by frequency, highest at the top
	QuickSortWords(storyWordMap, 0, numUniqueWords);

	// print the words
	PrintWordsToConsole(storyWordMap);

	// release memory
	DeleteWordCount(excludedWords);
	DeleteWordCount(storyWordMap);

	//return 0 on success b/c convention
	return 0;
}