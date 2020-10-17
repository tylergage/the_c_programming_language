
#include "bit_manipulation.h"

void run_cci_excercise_5_1(void)
{
	printf(CCI_5_1_INSTRUCTIONS);

	uint32_t M = 0x82222222;
	uint8_t N = 0x11;
	uint8_t pos = 12;

	printf("Example: M = 0x%8X, N = 0x%2X, pos = %d\n", M, N, pos);

	// Create a mask of all 0s
	uint32_t mask = 0x00000000;

	// Clear bits for M at correct position
	for(uint8_t i=0;i<8;i++)
	{
		M &= ~(1 << (pos+i));
	}

	printf("Cleared M (intermediate step): 0x%8X\n", M);

	// Put value of N in mask at correct possition
	mask |=  N;
	mask = mask << pos;


	// OR Mask with M
	M |= mask;

	printf("Solution: 0x%8X\n", M);
}

void run_cci_excercise_5_3(void)
{
	printf(CCI_5_1_INSTRUCTIONS);

	uint32_t input = 1775;
	uint8_t maxStreak = 0;
	uint8_t streakTracker = 0;

	printf("Example: %d, 0x%X\n", input, input);

	for(uint8_t i = 0; i<32 ; i++)
	{
		// Check if position is a 1
		if((input & 1<<i) != 0 )
		{
			// If yes increase tracker
			streakTracker++;
		}
		else
		{
			// If no check if current streak is max
			if(streakTracker > maxStreak)
			{
				maxStreak = streakTracker;
			}
			streakTracker = 0;
		}
	}

	// Do one last check if streak was at end of number
	if(streakTracker > maxStreak)
		{
			maxStreak = streakTracker;
		}

	printf("Max Streak: %d\n", maxStreak);
}

void run_cci_excercise_5_4(void)
{
	uint32_t input = 0xAAAAAAFF;
	bool foundSmallestGreater = false;
	bool foundSmallestLesser = false;
	uint32_t smallestGreater = 0;
	uint32_t smallestLesser = 0;
	uint32_t mask = 0;

	smallestGreater = input;
	smallestLesser = input;

	printf(CCI_5_4_INSTRUCTIONS);

	printf("Example: %X\n", input);

	// Count up the number of set bits
	for(int i=0;i<sizeof(input)*8;i++)
	{
		if(((0x01 << i) & input) != 0)
		{
			// Check if this bit works for smallest less than
			if(i>0)
			{
				if(((0x01 << (i-1) & input) == 0) && (foundSmallestLesser == false))
				{
					// We have found candidate for smallest less than
					// Clear bit, set bit to the right
					mask = ~(1 << i);
					smallestLesser &= mask;
					
					mask = (1 << (i-1));
					smallestLesser |= mask;

					foundSmallestLesser = true;
				}
			}

			// Check if this bit works for smallest greater than
			if((i < (sizeof(input)*8 - 1)) && (foundSmallestGreater == false))
			{
				if((0x01 << (i+1) & input) == 0)
				{
					// We have found candidate for smallest greater than
					// Clear bit, set bit to the left
					mask = ~(1 << i);
					smallestGreater &= mask;

					mask = (1 << (i+1));
					smallestGreater |= mask;

					foundSmallestGreater = true;
				}
			}
		}
		
		if(foundSmallestLesser == true && foundSmallestGreater == true)
		{
			break;
		}

	}

	printf("Smallest Greater: %X\n", smallestGreater);
	printf("Smallest Lesser: %X\n", smallestLesser);
}
