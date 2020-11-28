#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


// Question: Create a queue
#define MAX_QUEUE_SIZE 100

bool queue_init(int size);
bool queue_push(int element);
int queue_pop(void);
int queue_peek(void);

void queue_test(void);
