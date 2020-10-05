/*
	arrays_and_strings.c
	Created By: Tyler Gage
	10/4/2020
	Description: These are some coding excercise questions from "Cracking the Coding
	Interview". These are some excercises from Chapter 1. 
*/

#include "arrays_and_strings.h"
#include <stdbool.h>
#include <string.h>

void run_cci_excercise_1_1(void)
{
	printf(CCI_1_1_INSTRUCTIONS);

	// example 
	// abcdefg - ok
	// abcedfb - not ok

	// Brute force
	// iterate through array, check all other characters
	// each iteration we check all other characters, if we find a match, break
	// O(n*n)

	// Optimized
	// Hash Table, put all characters and frequency in hash table
	// iterate through 
	// O(n)

	// Answer, lets do a bit vector! Makes sense. Lesson learned here, 
	// you look at everything as a nail with a hammer, get away from iterating
	// through everything. Think about more optimized ways to reduce. If you think
	// that you have to iterate twice youn probably dont have to.


	char* input = "abcdefg";
	int i=0, j=0;
	bool duplicateFound = false;


	// BRUTE FORCE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	// Iterate through array to check for duplicate characters
	for(i=0;i<strlen(input);i++)
	{
		// Iterate through rest of array for each character
		for(j=i+1;j<strlen(input);j++)
		{
			if(input[i] == input[j])
			{
				// Handle situation where duplicate is found
				duplicateFound = true;
				break;
			}

		}
		if(duplicateFound == true)
		{
			break;
		}
	}

	if(duplicateFound)
	{
		printf("Ehh wrong, duplicate character found (Brute Force)\n");
	}
	else
	{
		printf("All unique, good to go (Brute Force)\n");
	}

	// Optimized >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	// Assume all lower case a-z
	int characterBitMask = 0x0000;
	int shiftValue = 0;

	for(i=0;i<strlen(input);i++)
	{
		// Calculate bit position of character
		shiftValue = input[i] - 'a';

		// Check if it has been seen yet
		if((characterBitMask & (1<<shiftValue)) != 0 )
		{
			duplicateFound = true;
			break;
		}
		else
		{
			characterBitMask |= (1<<shiftValue);
		}

	}

	if(duplicateFound)
	{
		printf("Ehh wrong, duplicate character found (Optimized)\n");
	}
	else
	{
		printf("All unique, good to go (Optimized)\n");
	}


}