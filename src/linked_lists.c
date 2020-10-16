#include "linked_lists.h"

static void generateDummyLinkedList(uint16_t numNodes, uint16_t maxVal);
static void printDummyLinkedList(void);
static void freeDummyLinkedList(void);

static Node* listHead = NULL;

////////// Public Functions //////////
void run_cci_excercise_2_1(void)
{
	Node* currNode;
	Node* runnerNode;
	Node* tempNode;

	printf(CCI_2_1_INSTRUCTIONS);
	
	generateDummyLinkedList(20, 5);
	printf("BEFORE: \n");
	printDummyLinkedList();

	currNode = listHead;

	// For each node check all other nodes for matches
	while(currNode != NULL)
	{
		runnerNode = currNode;

		while(runnerNode->next != NULL)
		{
			// Remove node if it matches
			if(runnerNode->next->data == currNode->data)
			{
				tempNode = runnerNode->next;
				runnerNode->next = runnerNode->next->next;

				// Make sure to free allocated data
				free(tempNode);
			}
			else
			{
				runnerNode = runnerNode->next;
			}
		}
		currNode = currNode->next;
	}

	printf("AFTER: \n");
	printDummyLinkedList();
	freeDummyLinkedList();
}

void run_cci_excercise_2_2(void)
{
	int input; 
	int listLength;

	Node *runner;

	printf(CCI_2_2_INSTRUCTIONS);
	
	generateDummyLinkedList(20, 50);
	printf("List: \n");
	printDummyLinkedList();
	
	printf("Enter element # from last:\n");
	scanf("%d", &input);

	// Measure out how long linked list is
	runner = listHead;
	listLength = 1;

	while(runner->next != NULL)
	{
		runner = runner->next;
		listLength++;
	}

	printf("List Length: %d\n", listLength);

	// Iterate to position
	runner = listHead;

	for(int i=0;i<(listLength - input);i++)
	{
		runner = runner->next;
	}

	printf("Data: %d\n", runner->data);

	freeDummyLinkedList();
}
////////// Private Functions //////////

// Create a dummy single linked list for problems, random values
static void generateDummyLinkedList(uint16_t numNodes, uint16_t maxVal)
{
	Node* nodePtr = NULL;

	// Initialize for random data values 
	srand(time(NULL)); 

	// Create node head
	nodePtr = (Node*) malloc(sizeof(Node));
	nodePtr->data = rand()%(maxVal+1);
	nodePtr->next = NULL;

	listHead = nodePtr;

	// Create rest of list
	for(int i=0;i< numNodes - 1;i++)
	{
		// Create next node
		nodePtr->next = (Node*) malloc(sizeof(Node));
		nodePtr = nodePtr->next;
		
		// Polulate Data
		nodePtr->data = rand()%(maxVal+1);
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