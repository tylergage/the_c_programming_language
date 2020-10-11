#include <pool_alloc.h> 

#if 0
  #define DEBUG_PRINT(a) printf a
#else
  #define DEBUG_PRINT(a) (void)0
#endif

static uint8_t g_pool_heap[SIZE_OF_GLOBAL_HEAP_BYTES]; 
static size_t g_block_sizes[MAX_BLOCK_SIZES];
static size_t g_block_size_count;
static uint8_t* g_allocation_ptrs[MAX_BLOCK_SIZES];

static void pool_print_block_info(uint32_t start, uint32_t length);

// Public Functions
bool pool_init(const size_t* block_sizes, size_t block_size_count) 
{ 
	uint8_t* ptr1;
	uint8_t* ptr2;
	
	// Check inputs
	if(block_size_count > MAX_BLOCK_SIZES)
	{
		printf("Error: Too many block sizes, max number of sizes is %u\n", MAX_BLOCK_SIZES);
		return false;
	}

	// Clear heap data
	memset(g_pool_heap, 0, SIZE_OF_GLOBAL_HEAP_BYTES);

	// Save global data for heap allocator
	g_block_size_count = block_size_count;

	for(uint32_t i=0; i < g_block_size_count; i++)
	{
		g_block_sizes[i] = block_sizes[i];

		// Each block 
		uint32_t numBlocksInZone = ((uint32_t)SIZE_OF_GLOBAL_HEAP_BYTES / (uint32_t)g_block_size_count) / ((uint32_t) g_block_sizes[i] + sizeof(uint8_t*));
		uint32_t totalBlockSize = g_block_sizes[i] + sizeof(uint8_t*);

		DEBUG_PRINT(("Zone: %u, Blocks in Zone: %u, Data Block Sizes: %u, Total Block Size: %u\n", i, numBlocksInZone, (unsigned int) g_block_sizes[i], totalBlockSize));

		ptr1 = g_pool_heap + ((uint32_t)SIZE_OF_GLOBAL_HEAP_BYTES / (uint32_t)g_block_size_count)*i;
	    ptr2 = ptr1 + totalBlockSize + sizeof(uint8_t*);

	    // Initialize allocation pointer for this block used in malloc and free
	    g_allocation_ptrs[i] = ptr1;

		// Initialize all blocks in the zone
		for(uint32_t j = 0; j<numBlocksInZone; j++)
		{
			// Save pointer in heap
			if(ptr2 != NULL)
			{
				memcpy(ptr1, &ptr2, sizeof(uint8_t*));
			}

			// Move pointers to next block, make sure to handle last block which should point to NULL
			if(j < (numBlocksInZone-2))
			{
				ptr1 = ptr2 - sizeof(uint8_t*);
				ptr2 = ptr1 + totalBlockSize + sizeof(uint8_t*);	
			}
			else
			{
				if(ptr2 != NULL)
				{
					ptr1 = ptr2 - sizeof(uint8_t*);
				}
				ptr2 = NULL;
			}		
		}
	}

	DEBUG_PRINT(("Heap Pointer = 0x%X, (%d)\n", (unsigned int) g_pool_heap, (unsigned int) g_pool_heap));
	return true;
} 

// Assumption data being pointed to is garbage, user is expected to initialize after returned block
void* pool_malloc(size_t n)
{
	uint32_t index=0;
	bool matchFound=false;
	void* rtnPtr = NULL;

	// Check that n is a valid size, and find index in saved block sizes
 	for(index=0; index < g_block_size_count; index++)
 	{
 		if(n == g_block_sizes[index])
 		{
 			matchFound = true;
 			break;
 		}
 	}

 	if(matchFound == false)
 	{
 		printf("ERROR: Pool malloc called with an invalid size\n");
 		return NULL;
 	}

 	// Check if block zone is completely filled up
 	if(g_allocation_ptrs[index] == NULL)
 	{
 		printf("ERROR: Block zone full\n");
		return NULL;
 		// Further improvement could include going to a boundary with blocks
 		// that are bigger and use those
 	}

 	DEBUG_PRINT(("Allocation Pointer = 0x%X, (%d) BEFORE MALLOC\n", (unsigned int) g_allocation_ptrs[index], (unsigned int) g_allocation_ptrs[index]));
 	// Save return value of allocated data for user
 	rtnPtr = (void*) (g_allocation_ptrs[index] + sizeof(uint8_t*));

 	// Update allocation pointer to next free element
 	memcpy(&g_allocation_ptrs[index], g_allocation_ptrs[index], sizeof(uint8_t*));

 	// Make sure to properly handle situation where we are filling up a zone
 	if(g_allocation_ptrs[index] != NULL)
 	{
		g_allocation_ptrs[index] -= sizeof(uint8_t*); // want to point to the meta data
 	}

 	DEBUG_PRINT(("Allocation Pointer = 0x%X, (%d) AFTER MALLOC\n", (unsigned int) g_allocation_ptrs[index], (unsigned int) g_allocation_ptrs[index]));

 	return rtnPtr;
}

// Asumption that user will return proper pointer at beginning of a block
void pool_free(void* ptr)
{
	void* tempPtr = NULL;
	bool matchFound=false;
	uint32_t index=0;

	// Verify lower bound of pointer
	if((uint8_t*)ptr < g_pool_heap)
	{
		printf("Warning: call to pool free was with a pointer not in pool heap\n");
		return;
	}

	// Find which zone this pointer is in
	for(index=1;index<(uint32_t)g_block_sizes;index++)
	{
		tempPtr = (void*)g_pool_heap + ((uint32_t)SIZE_OF_GLOBAL_HEAP_BYTES / (uint32_t)g_block_size_count)*index;
		if(ptr < tempPtr)
		{
			DEBUG_PRINT(("Pointer found in zone %u\n", (index-1))); // DEBUG remove later
			matchFound = true;
			break;
		}
	}

	index--; // Need to decrement for the right zone, its less than next zone boundary

	if(matchFound == false)
	{
		printf("Warning: call to pool free was with a pointer not in pool heap\n");
		return;
	}

	// Set allocation pointer to the zone being freed, and set next pointer to previously free block
	// Be careful handling offsets of pointer for each block
	DEBUG_PRINT(("Allocation Pointer = 0x%X, (%d) BEFORE FREE\n", (unsigned int) g_allocation_ptrs[index], (unsigned int) g_allocation_ptrs[index]));
	tempPtr = g_allocation_ptrs[index];
	tempPtr += sizeof(uint8_t*);

	g_allocation_ptrs[index] = ptr;
	g_allocation_ptrs[index] -= sizeof(uint8_t*);

	memcpy(g_allocation_ptrs[index], &tempPtr, sizeof(uint8_t*));

	DEBUG_PRINT(("Allocation Pointer = 0x%X, (%d) AFTER FREE\n", (unsigned int) g_allocation_ptrs[index], (unsigned int) g_allocation_ptrs[index]));
}

// Private Functions
// Used for debugging purposes
static void pool_print_block_info(uint32_t start, uint32_t length)
{
	for(uint32_t i=0;i<length;i++)
	{
		printf("%u: 0x%02X: 0x%02X\n", (unsigned int) &g_pool_heap[i+start], i+start, g_pool_heap[i+start]);	
	}
}
