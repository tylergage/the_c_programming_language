#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH	15

typedef struct wordCounter_t
{
	char word[MAX_WORD_LENGTH];
	int count;
} wordCounter_t;

const char* instruction_excercise_1_13(void);
void run_excercise_1_13(void);
