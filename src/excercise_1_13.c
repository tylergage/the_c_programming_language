/*
	excercise_1_13.c
	Created By: Tyler Gage
	9/5/2020
	Description: Excercise 1-13 from the book, "C Programming Language"
	Write a program to print a histogram of the lengths of words in its input. 
	It is easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging.
	Note: This is actually incorrect from the book. I was supposed to do lengths, this is dong the individual
	words. Its actually a little more challenging, so going to leave it as is.
*/

#include "excercise_1_13.h"

#define MAX_INPUT 		100
#define MAX_WORDS 		100

static const char* INSTRUCTIONS = "Write a program to print a histogram of the lengths of words in its input. Enter the word \"DONE\" when finished :";
static const char* EXIT_PROMPT = "DONE";

static wordCounter_t wordTracker[MAX_WORDS];

static void printHistogram(void);

// Public Functions
const char* instruction_excercise_1_13(void)
{
	return INSTRUCTIONS;
}

void run_excercise_1_13(void)
{
	char userInput[MAX_INPUT] = {0};
	int i = 0;
	bool wordFound = false;

	printf("Exercise 1 - 13 :\n%s\n", instruction_excercise_1_13());
	
	// Iterate through input word by word
	while(scanf("%s", userInput) != EOF)
	{
		// First check it all input is received
		if(strcmp(userInput,EXIT_PROMPT) == 0) 
		{
			break;
		}

		// Check if word is already in tracker
		wordFound = false;
		i=0;

		while(wordFound == false)
		{
			if(wordTracker[i].count == 0) // Insert at end of list, new word
			{
				strcpy(wordTracker[i].word,userInput);
				wordTracker[i].count++;
				wordFound = true;
			}
			else if(strcmp(wordTracker[i].word,userInput) == 0) // Add to count if already in list
			{
				wordTracker[i].count++;
				wordFound = true;
			}
			i++;
		}
	}

	printHistogram();

	printf("Excercise complete, returning to main menu...\n");
}


// Private Functions
static void printHistogram(void)
{
	int i,j;

	printf("Creating histogram \n>>>>>>>>>>>>>\n");

	for(i=0;i<MAX_WORDS;i++)
	{
		if(wordTracker[i].count == 0) // Check if we are at the end
		{
			printf(">>>>>>>>>>>>>\n");
			break;
		}

		// Print word and bar graph
		printf("%15s:", wordTracker[i].word);
		for(j=0;j<wordTracker[i].count;j++)
		{
			printf("#");
		}
		printf("\n");
	}

}

