#include <stdio.h>
#include <stdint.h>

#include "user_input.h"

#include "excercise_1_12.h"
#include "excercise_1_13.h"

static void gui(void);

int main(int argc, char** argv)
{
	printf("Welcome to C Programming Excercises!\n");
	gui();
}


static void gui(void)
{
	char userInput[MAX_INPUT];
	int i;
	bool commandFound;

	while(scanf("%s", userInput) != EOF)
	{
		commandFound = false;
		for(i=0;i<sizeof(commandTable)/sizeof(commandTable[0]);i++)
		{
			if(strcmp(commandTable[i].command,userInput) == 0)
			{
				commandTable[i].command_function(userInput);
				commandFound = true;
				break;
			}
		}
		
		if(commandFound == false)
		{
			printf("Unknown command, enter \"help\" for more info\n");
		}
	}
}



void ui_info(char* userInput)
{
	printf("TODO list out program information\n");
}

void ui_help(char* userInput)
{
	printf("TODO list out program help\n");
}

void ui_exit(char* userInput)
{
	printf("Exit program, bye!...\n");
}

void ui_excercise_1_12(char* userInput)
{
	run_excercise_1_12();
}

void ui_excercise_1_13(char* userInput)
{
	run_excercise_1_13();
}


