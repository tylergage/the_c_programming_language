
#include "queue.h"

#if 0
  #define DEBUG_PRINT(a) printf a
#else
  #define DEBUG_PRINT(a) (void)0
#endif

static int queue[MAX_QUEUE_SIZE+1] = {0};
static int queueSize = 0;

static int pushIndex = 0;
static int popIndex = 0;

bool queue_init(int size)
{
	// Check Inputs
	if(queueSize > MAX_QUEUE_SIZE)
	{
		printf("Error: queue size is too big\n");
		return false;
	}


	// Initialize local variables
	memset(queue, 0, MAX_QUEUE_SIZE*sizeof(int));

	queueSize = size;

	pushIndex = -1;
    popIndex = -1;

    return true;
}

bool queue_push(int element)
{
	// Check first that queue is not full
	if((popIndex > pushIndex) && (popIndex - pushIndex == 1))
	{
		DEBUG_PRINT(("Error: Queue full!!!\n"));
		return false;
	}
	else if(popIndex == 0 && pushIndex == (queueSize-1)) // Boundary case
	{
		DEBUG_PRINT(("Error: Queue full!!!\n"));
		return false;
	}

	if(pushIndex == -1 && popIndex == -1)
	{
		pushIndex = 0;
		popIndex = 0;
		queue[pushIndex] = element;
		DEBUG_PRINT(("PUSH1 : %d pushed at index %d\n", element, pushIndex));
	}
	else if(pushIndex == (queueSize-1))
	{
		pushIndex = 0;
		queue[pushIndex] = element;
		DEBUG_PRINT(("PUSH2 : %d pushed at index %d\n", element, pushIndex));
	} 
	else
	{
		pushIndex++;
		queue[pushIndex] = element;
		DEBUG_PRINT(("PUSH3 : %d pushed at index %d\n", element, pushIndex));
	}

	DEBUG_PRINT(("PUSH : POP IDX: %d, PUSH IDX: %d\n", popIndex, pushIndex));

	return true;
}

int queue_pop(void)
{
	int retElement = -1;

	if(pushIndex == -1 && popIndex == -1)
	{
		DEBUG_PRINT(("Error: Queue empty!!!\n"));
		return -1;
	}

	if(pushIndex == popIndex) // Handle lase element
	{
		retElement = queue[popIndex];
		DEBUG_PRINT(("POP1 : %d popped at index %d\n", retElement, popIndex));
		pushIndex = -1;
		popIndex = -1;
	}
	else if(popIndex == queueSize-1)
	{
		retElement = queue[popIndex];
		DEBUG_PRINT(("POP2 : %d popped at index %d\n", retElement, popIndex));
		popIndex = 0;
	}
	else
	{
		retElement = queue[popIndex];
		DEBUG_PRINT(("POP3 : %d popped at index %d\n", retElement, popIndex));
		popIndex++;
	}

	DEBUG_PRINT(("POP : POP IDX: %d, PUSH IDX: %d\n", popIndex, pushIndex));

	return retElement;
}

int queue_peek(void)
{
	int retElement = -1;

	if(pushIndex == -1 && popIndex == -1)
	{
		printf("Error: Queue empty!!!\n");
		return -1;
	}

	retElement = queue[popIndex];

	return retElement;
}

void queue_test(void)
{
	printf("Test queue:\n");

	// TEST 1
	queue_init(10);

	for(int i=0;i<10;i++)
	{
		if(queue_push(i) != true)
		{
			printf("Test 1 failed at %d!!!\n", i);
		}
	}

	for(int i=0;i<10;i++)
	{
		int element = queue_pop();
		printf("Pop: %d\n", element);
	}

	// Do one more pop just to verify the queue is empty
	printf("Pop: %d\n", queue_pop());

}

int queue_size(void)
{
	return 0;
}
