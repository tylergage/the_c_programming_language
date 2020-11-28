
#include "queue.h"

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
	if(popIndex - pushIndex == 1)
	{
		printf("Error: Queue full!!!\n");
		return false;
	}
	if(popIndex == 0 && pushIndex == (queueSize-1)) // Boundary case
	{
		printf("Error: Queue full!!!\n");
		return false;
	}

	// Add data to queue
	queue[pushIndex] = element;
	pushIndex++;
	
	if(pushIndex >= queueSize || pushIndex >= MAX_QUEUE_SIZE)
	{
		pushIndex = 0;
	}

	return true;
}

int queue_pop(void)
{
	int retElement = -1;

	if(pushIndex == popIndex)
	{
		printf("Error: Queue empty!!!\n");
		return -1;
	}

	retElement = queue[popIndex];
	popIndex++;

	if(popIndex >= queueSize || popIndex >= MAX_QUEUE_SIZE)
	{
		popIndex = 0;
	}

	return retElement;
}

int queue_peek(void)
{
	int retElement = -1;

	if(pushIndex == popIndex)
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
		printf("Pop: %d\n", queue_pop());
	}

	// Do one more pop just to verify the queue is empty
	queue_pop();

}

int queue_size(void)
{
	return 0;
}
