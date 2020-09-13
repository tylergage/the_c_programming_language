/*
	ui.c
	Created By: Tyler Gage
	9/13/2020
	Description: Module for handling user interface with program user. 
	Defines and processes all input from user to use the program, and
	hadles output to user. 
*/

#include "ui.h"

#define EXIT_PROMPT "EXIT"

void ui(void)
{
	char userInput[MAX_INPUT];
	int i;
	bool commandFound;

	while(scanf("%s", userInput) != EOF)
	{
		// First off, check if user wants to exit and handle
		if(strcmp(EXIT_PROMPT, userInput) == 0)
		{
			break;
		}

		// Check if command exists in the table, and if found execute function
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

	printf("Exit program, bye!...\n");
}

void ui_info(char* userInput)
{
	printf("TODO list out program information\n");
}

void ui_help(char* userInput)
{
	int i;

	printf("<<<<<<<< Available commands >>>>>>>>\n");
	
	for(i=0;i<sizeof(commandTable)/sizeof(commandTable[0]);i++)
	{
		printf("%s\n", commandTable[i].command);
	}

	printf("%s\n", EXIT_PROMPT);

	printf("<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>\n");
}

void ui_excercise_1_12(char* userInput)
{
	run_excercise_1_12();
}

void ui_excercise_1_13(char* userInput)
{
	run_excercise_1_13();
}