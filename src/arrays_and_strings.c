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

#define MAX_USER_INPUT 100

static bool isWhiteSpace(char c);
static char * mGetLine(char * line);

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

	printf("Example: Input = %s\n", input);

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

void run_cci_excercise_1_2(void)
{
	printf(CCI_1_2_INSTRUCTIONS);

	char* str1 = "abc";
	char* str2 = "cae";

	printf("Example: String 1 = %s String 2 = %s\n", str1, str2);

	int str1Count[128] = {0};
	int str2Count[128] = {0};

	bool mismatchFound = false;

	// ToDo: Check inputs - lengths of strings, strings same lengths, etc


	// Iterate through strings, count frequency of characters
	for(int i = 0; i<strlen(str1);i++)
	{
		str1Count[(int)str1[i]]++;
		str2Count[(int)str2[i]]++;
	}

	// Iterate through character counts, to see if they match
	for(int i = 0; i<sizeof(str1Count)/sizeof(str1Count[0]); i++)
	{
		if(str1Count[i] != str2Count[i])
		{
			mismatchFound = true;
			break;
		}
	}

	if(mismatchFound == true)
	{
		printf("NO, they are not a permutation\n");
	}
	else
	{
		printf("YES, they are a permutation\n");
	}
}

void run_cci_excercise_1_3(void)
{
	char input[MAX_USER_INPUT] = "Mr Jon Smith  y 	h  ";
	char inputUrl[MAX_USER_INPUT];
	const char* whiteSpaceReplacement = "%20";

	int j=0;

	printf("Example string to URLify:\n");
	printf("%s\n", input);

	for(int i=0;i<strlen(input);i++)
	{
		if(isWhiteSpace(input[i]))
		{
			// Increment until we get to next non white space
			while(isWhiteSpace(input[i])) 
			{
				i++;
			}

			if(i<strlen(input))
			{
				// Put %20 in URL version of string
				memcpy(&inputUrl[j], whiteSpaceReplacement, strlen(whiteSpaceReplacement));
				j+=strlen(whiteSpaceReplacement);
			}
			else
			{
				break;
			}
		}
			
		inputUrl[j++] = input[i];
	}

	inputUrl[j] = '\0';

	printf("%s\n", inputUrl);
}



static bool isWhiteSpace(char c)
{
	if( c == ' '  ||
		c == '\t')
	{
		return true;
	}
	else
	{
		return false;
	}
}