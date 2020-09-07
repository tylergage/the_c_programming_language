/*
	excercise_1_13.c
	Created By: Tyler Gage
	9/5/2020
	Description: Excercise 1-13 from the book, "C Programming Language"
	Write a program to print a histogram of the lengths of words in its input. 
	It is easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging.
	*Assumes all words are only separated by a single space, input starts with first word
*/

#include "excercise_1_13.h"

#define MAX_INPUT 		100
#define MAX_WORD_LENGTH 15
#define MAX_WORDS 		30

static const char* DESCRIPTION = "Write a program to print a histogram of the lengths of words in its input :";

const char* description_excercise_1_13(void)
{
	return DESCRIPTION;
}

void run_excercise_1_13(void)
{
	char userInput[MAX_INPUT];
	char wordTracker[MAX_WORDS][MAX_WORD_LENGTH];
	int wordCount,i,j,k;

	// Initialize variables
	i=j=k=wordCount=0;

	for(i=0;i<MAX_WORDS;i++)
	{
		memset(wordTracker[i], '\0', sizeof(wordTracker[i]));
	}

	printf("Exercise 1 - 13 :\n %s\n", description_excercise_1_13());

	while((userInput[i++]=getchar())!='\n')
	{
		// Check if we are at the end of a word
		if(userInput[i-1] == ' ')
		{
			wordTracker[j][k] = '\n';
			j++;
			k=0;
			wordCount++;
		}
		else
		{
			wordTracker[j][k++] = userInput[i-1];
		}
	}

	// Need to make sure we account for the last word
	wordCount++; 
	wordTracker[j][k] = '\n';

	for(i=0;i<wordCount;i++)
	{
		printf("%s",wordTracker[i]);
	}

	printf("DONE!\n");
}
