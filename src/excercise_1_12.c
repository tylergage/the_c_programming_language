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

	while((userInput[i++]=getchar())!='\n')
	{
		if(userInput[i-1]==' ')
		{
			userInput[i-1] = '\n';	
		}
	}

	printf("%s", userInput);

	printf("DONE!\n");
}


