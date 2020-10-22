#include "linked_lists.h"

static bool randInit = false;

static void generateDummyLinkedList(uint16_t numNodes, uint16_t maxVal);
static void printDummyLinkedList(void);
static void freeDummyLinkedList(void);

static Node* generateNewDummyLinkedList(uint16_t numNodes, uint16_t maxVal);
static void printNewDummyLinkedList(Node* listHead);
static void freeNewDummyLinkedList(Node* listHead);

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

void run_cci_excercise_2_4(void)
{
	int partition = 5;
	Node* runner;
	Node* greaterHead;
	Node* lesserHead;
	Node* greaterLast;
	Node* lesserLast;
	Node* tempNode;

	printf(CCI_2_4_INSTRUCTIONS);
	printf("Example Partition Value = %d\n", partition);
	
	generateDummyLinkedList(7, 10);

	printf("Before: \n");
	printDummyLinkedList();

	// Initialize pointers
	runner = listHead;
	
	// Create 2 lists, one before partition and one after
	greaterHead = NULL;
	lesserHead = NULL;
	greaterLast = NULL;
	lesserLast = NULL;

	while(runner != NULL)
	{
		tempNode = runner->next;

		// Add node to appropriate list
		if(runner->data >= partition)
		{
			if(greaterLast == NULL)
			{
				greaterHead = runner;
				greaterLast = runner;
				runner->next = NULL;
			}
			else
			{
				greaterLast->next = runner;
				runner->next = NULL;
				greaterLast = runner;
			}
		}
		else
		{
			if(lesserLast == NULL)
			{
				lesserHead = runner;
				lesserLast = runner;
				runner->next = NULL;
			}
			else
			{
				lesserLast->next = runner;
				runner->next = NULL;
				lesserLast = runner;
			}
		}

		runner = tempNode;
	}

	// Combine lists
	lesserLast->next = greaterHead;
	listHead = lesserHead;

	printf("After: \n");
	printDummyLinkedList();
}

void run_cci_excercise_2_5(void)
{
	Node* list1Head;
	Node* list2Head;
	Node* runner1;
	Node* runner2;

	Node* outputListRunner;
	Node* outputListHead;

	int temp=0;
	int carryVal=0;

	list1Head = generateNewDummyLinkedList(3, 9);
	list2Head = generateNewDummyLinkedList(3, 9);

	printf(CCI_2_5_INSTRUCTIONS);

	printf("Example:\n");
	printf("Input: List 1\n");
	printNewDummyLinkedList(list1Head);

	printf("Input: List 2\n");
	printNewDummyLinkedList(list2Head);

	runner1 = list1Head;
	runner2 = list2Head;

	// Initialize output list
	outputListHead = (Node*) malloc(sizeof(Node));
	outputListHead->data = 0;
	outputListHead->next = NULL;

	outputListRunner = outputListHead;

	while(runner1!=NULL && runner2!=NULL)
	{
		temp = runner1->data + runner2->data + carryVal;

		if(temp < 10)
		{
			outputListRunner->data = temp;
			carryVal = 0;
		}
		else
		{
			outputListRunner->data = temp%10;
			carryVal = 1;
		}

		if(runner1->next!=NULL && runner2->next!=NULL)
		{
			outputListRunner->next = (Node*) malloc(sizeof(Node));
			outputListRunner = outputListRunner->next;
			outputListRunner->data = 0;
			outputListRunner->next = NULL;
		}

		runner1= runner1->next;
		runner2= runner2->next;
	}

	if(carryVal > 0)
	{
		outputListRunner->next = (Node*) malloc(sizeof(Node));
		outputListRunner = outputListRunner->next;

		outputListRunner->data = carryVal;
		outputListRunner->next = NULL;
	}

	printf("Output List:\n");
	printNewDummyLinkedList(outputListHead);

	freeNewDummyLinkedList(list1Head);
	freeNewDummyLinkedList(list2Head);
	freeNewDummyLinkedList(outputListHead);


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

// Create a dummy single linked list for problems, random values, return head
static Node* generateNewDummyLinkedList(uint16_t numNodes, uint16_t maxVal)
{
	Node* nodePtr = NULL;
	Node* head;

	// Initialize for random data values 
	if(randInit == false)
	{
		srand(time(NULL)); 
		randInit = true;
	}

	// Create node head
	nodePtr = (Node*) malloc(sizeof(Node));
	nodePtr->data = rand()%(maxVal+1);
	nodePtr->next = NULL;

	head = nodePtr;

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

	return head;
}

// Print generated linked list, of a specific list
static void printNewDummyLinkedList(Node* mlistHead)
{
	Node* nodePtr = NULL;
	int i = 0;

	nodePtr = mlistHead;

	printf("Linked List:\n");
	
	while(nodePtr != NULL)
	{
		printf("Node %d: %d\n", i++, nodePtr->data);
		nodePtr = nodePtr->next;
	}
}

// Make sure memory is freed up after we are done with list, of a specified list
static void freeNewDummyLinkedList(Node* mlistHead)
{
	Node* nodePtr1 = NULL;
	Node* nodePtr2 = NULL;

	nodePtr1 = mlistHead;
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