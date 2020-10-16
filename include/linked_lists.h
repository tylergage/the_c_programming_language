#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_OF_NODES 30

#define CCI_2_1_INSTRUCTIONS "Remove Dups: Write code to remove duplicates from an unsorted linked list\n"
#define CCI_2_2_INSTRUCTIONS "Last k: Find data at kth element from the end\n"

typedef struct Node
{
	struct Node* next;
	int data;
} Node;


void run_cci_excercise_2_1(void);
void run_cci_excercise_2_2(void);
