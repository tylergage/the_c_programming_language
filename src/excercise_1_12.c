/*
	excercise_1_12.c
	Created By: Tyler Gage
	9/5/2020
	Description: Excercise 1-12 from the book, "C Programming Language"
	Write a program that prints out its input one word per line, write any line
	*Assumes all words are only separated by a single space
*/

#include "excercise_1_12.h"

#define MAX_INPUT 100

static const char* DESCRIPTION = "Write a program that prints out its input one word per line, write any line:";
static const char* EXIT_PROMPT = "DONE";

const char* description_excercise_1_12(void)
{
	return DESCRIPTION;
}

void run_excercise_1_12(void)
{
	char userInput[MAX_INPUT];

	printf("Exercise 1 - 12 :\n %s\n", description_excercise_1_12());

	// Iterate through input
	while(scanf("%s", userInput) != EOF)
	{
		// First check it all input is received
		if(strcmp(userInput,EXIT_PROMPT) == 0) 
		{
			break;
		}

		// Print each word as its own line
		printf("%s\n",userInput );
	}

	printf("DONE!\n");
}


