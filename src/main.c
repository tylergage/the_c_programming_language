#include <stdio.h>
#include <stdint.h>

#include "excercise_1_12.h"
#include "excercise_1_13.h"

int main(int argc, char** argv)
{
	int i;

	printf("argc: %d\n", argc);

	for(i=0;i<argc;i++)
	{
		printf("arg %d: %s\n", i, argv[i]);
	}

	run_excercise_1_13();
}

