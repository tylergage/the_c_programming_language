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

const char* description_excercise_1_12(void)
{
	return DESCRIPTION;
}

void run_excercise_1_12(void)
{
	char userInput[MAX_INPUT];
	int i=0;

	printf("Exercise 1 - 12 :\n %s\n", description_excercise_1_12());

	// Iterate through input
	while((userInput[i++]=getchar())!='\n')
	{
		// Detect end of words, by space (assumption all words are separated by single space)
		if(userInput[i-1]==' ')
		{
			userInput[i-1] = '\n';	
		}
	}

	printf("%s", userInput);

	printf("DONE!\n");
}


