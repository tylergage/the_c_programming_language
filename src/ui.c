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

	printf("Closing program... bye!\n");
}

void ui_info(char* userInput)
{
	printf("The purpose of this program is to demonstrate a" 
		"number of different programming excercises in the C"
		"programming language. Questions are taken from different "
		"books or the internet and chosen on a whim for what I find "
		"interesting or would serve as a good challenge. There is a "
		"CLI framework present for navigating different questions "
		"and excercises. This program is created and maintained "
		"by Tyler Gage. \n");
}

void ui_help(char* userInput)
{
	int i;

	printf("<<<<<<<< Available commands >>>>>>>>\n");
	
	for(i=0;i<sizeof(commandTable)/sizeof(commandTable[0]);i++)
	{
		printf("%s: %s\n", 
			commandTable[i].command,
			commandTable[i].command_description);
	}

	printf("%s: Close program\n", EXIT_PROMPT);

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