#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 40
#define MAX_EXCLUDE_SIZE 500
typedef struct WordCount_type {
	char* word;
	int count;
} WordCount;

int CountWordsInFile(char* argFileName);
void RemovePunctuationMakeUpperCase(char* argWord);
void PrintWordsToConsole(WordCount* argWordCount);
int NumUniqueWords(WordCount* argWordCount);

WordCount* CreateWordCountArray(int argNumberOfWords);
void DeleteWordCount(WordCount* argWordCount);
WordCount* ReadExclusionFile(char* argFileName);
WordCount* ReadStoryFile(char* argFileName, WordCount* argExclusionList);
bool WordExistsInWordCount(WordCount* argWordCount, char* argBuffer);
void UpdateWordCount(WordCount* argWordCount, char* argBuffer);

void QuickSortWords(WordCount* argWordCount, int argLow, int argHigh);
int QuickSortPartition(WordCount* argWordCount, int argLow, int argHigh);