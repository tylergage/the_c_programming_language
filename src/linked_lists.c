#include "linked_lists.h"

static void generateDummyLinkedList(void);
static void printDummyLinkedList(void);
static void freeDummyLinkedList(void);

static Node* listHead = NULL;

////////// Public Functions //////////
void run_cci_excercise_2_1(void)
{
	printf(CCI_2_1_INSTRUCTIONS);
	
	generateDummyLinkedList();

	printDummyLinkedList();

	freeDummyLinkedList();
}

////////// Private Functions //////////

// Create a dummy single linked list for problems
static void generateDummyLinkedList(void)
{
	Node* nodePtr = NULL;

	// Initialize for random data values 
	srand(time(NULL)); 

	// Create node head
	nodePtr = (Node*) malloc(sizeof(Node));
	nodePtr->data = rand();
	nodePtr->next = NULL;

	listHead = nodePtr;

	// Create rest of list
	for(int i=0;i< NUM_OF_NODES - 1;i++)
	{
		// Create next node
		nodePtr->next = (Node*) malloc(sizeof(Node));
		nodePtr = nodePtr->next;
		
		// Polulate Data
		nodePtr->data = rand();
		nodePtr->next = NULL;

	}

}

// Print generated linked list
static void printDummyLinkedList(void)
{
	Node* nodePtr = NULL;
	int i = 0;

	nodePtr = listHead;

	printf("Linked List:\n");
	
	while(nodePtr != NULL)
	{
		printf("Node %d: %d\n", i++, nodePtr->data);
		nodePtr = nodePtr->next;
	}

}

// Make sure memory is freed up after we are done with lists
static void freeDummyLinkedList(void)
{
	Node* nodePtr1 = NULL;
	Node* nodePtr2 = NULL;

	nodePtr1 = listHead;
	nodePtr2 = nodePtr1->next;

	// Free all memory for linked list
	while(nodePtr1 != NULL)
	{
		free(nodePtr1);

		if(nodePtr2 != NULL)
		{
			nodePtr1 = nodePtr2;
			nodePtr2 = nodePtr1->next;
		}
		else
		{
			break;
		}
	}
}