/** WordCloud.h
 * ===========================================================
 * Name: CS220, Spring 2020
 *
 * Purpose:  Produces a word cloud given a word list and their
 * 			 frequency.
 * ===========================================================*/
#pragma once
#include "PEX1.h"
#include <stdio.h>

int BuildWordCloud(WordCount* argWordCount, char* argFileName, int argNumWords);