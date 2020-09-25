/** WordCloud.c
 * ===========================================================
 * Name: CS220, Spring 2020
 *
 * Purpose:  Produces a word cloud given a word list and thier
 * 			 frequency.
 * ===========================================================*/


#include "WordCloud.h"

 /** -------------------------------------------------------------------
  * Build the word cloud.
  * @param argWordCounts - parallel array with frequency of words
  * @param argWords  - parallel array with word list
  * @param argFileName - html file to output word cloud to
  * @return returns 1 on success and 0 on failure
   -------------------------------------------------------------------*/
int BuildWordCloud(WordCount* argWordCount, char* argFileName, int argNumWords)
{
	// open/check to see if file is valid
	FILE* filePtr = NULL;

	filePtr = fopen(argFileName, "w+");
	
	if (filePtr == NULL)
	{
		return -2;
	}

	// print header and style information to output file
	fprintf(filePtr, "<!DOCTYPE html>\n<html>\n<head>\n<style>\ntext1{\nfont-size: 10px;\ncolor: white;\n}\ntext2{\nfont-size: 20px;\ncolor: blue;\n}\ntext3{\nfont-size: 30px;\ncolor: green;\n}\ntext4{\nfont-size: 40px;\ncolor: yellow;\n}\ntext5{\nfont-size: 50px;\ncolor: orange;\n}\ntext6{\nfont-size: 60px;\ncolor: red;\n}\n</style>\n<title>Word Cloud</title>\n</head>\n<body bgcolor = \"#000000\">\n<center>\n");

	// print the words with the style according to their frequency
	for (int i = 0; argWordCount[i].word != NULL; i++) {
		if (argWordCount[i].count == 1) {
			fprintf(filePtr, "<text1>%s</text1>\n", argWordCount[i].word);
		}
		else if (argWordCount[i].count == 2) {
			fprintf(filePtr, "<text2>%s</text2>\n", argWordCount[i].word);
		}
		else if (argWordCount[i].count == 3) {
			fprintf(filePtr, "<text3>%s</text3>\n", argWordCount[i].word);
		}
		else if (argWordCount[i].count == 4) {
			fprintf(filePtr, "<text4>%s</text4>\n", argWordCount[i].word);
		}
		else if (argWordCount[i].count == 5) {
			fprintf(filePtr, "<text5>%s</text5>\n", argWordCount[i].word);
		}
		else if (argWordCount[i].count > 5) {
			fprintf(filePtr, "<text6>%s</text6>\n", argWordCount[i].word);
		}
	}

	// print out the footer information
	fprintf(filePtr, "</center>\n</body>\n</html>");

	// close the file and return
	fclose(filePtr);
	return 0;
}