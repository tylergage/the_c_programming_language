#include <stdio.h> 
#include <stdint.h> 
#include <stdbool.h> 
#include <string.h>
#include <pool_alloc.h> 

#define MAX_BLOCK_SIZES 10
#define SIZE_OF_GLOBAL_HEAP_BYTES 65536

static uint8_t g_pool_heap[SIZE_OF_GLOBAL_HEAP_BYTES]; 
static size_t g_block_sizes[MAX_BLOCK_SIZES];
static size_t g_block_size_count;
static uint8_t* g_allocation_ptrs[MAX_BLOCK_SIZES];

static bool heap_initialized = false;

static void pool_print_block_info(uint32_t start, uint32_t length);

// Public Functions
bool pool_init(const size_t* block_sizes, size_t block_size_count) 
{ 
	
	heap_initialized = false;

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

	// Save local file data for heap allocator
	g_block_size_count = block_size_count;

	for(uint32_t i=0; i < g_block_size_count; i++)
	{
		g_block_sizes[i] = block_sizes[i];

		uint32_t numBlocksInZone = ((uint32_t)SIZE_OF_GLOBAL_HEAP_BYTES / (uint32_t)g_block_size_count) / ((uint32_t) g_block_sizes[i] + sizeof(uint8_t*));
		uint32_t totalBlockSize = g_block_sizes[i] + sizeof(uint8_t*);

		printf("Blocks in Zone: %u, Total Block Size: %u\n", numBlocksInZone, totalBlockSize);

		ptr1 = g_pool_heap + ((uint32_t)SIZE_OF_GLOBAL_HEAP_BYTES / (uint32_t)g_block_size_count)*i;
	    ptr2 = ptr1 + totalBlockSize + sizeof(uint8_t*);

	    // Initialize allocation pointer for this block used in malloc and free
	    g_allocation_ptrs[i] = ptr1;

		// Initialize all blocks in the zone
		for(uint32_t j = 0; j<numBlocksInZone; j++)
		{
			// Save pointer in heap
			memcpy(ptr1, &ptr2, sizeof(uint8_t*));

			// Move pointers to next block, make sure to handle last block which should point to NULL
			if(j < (numBlocksInZone - 1))
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

	heap_initialized = true;

	return true;
} 

void* pool_malloc(size_t n)
{
	uint32_t index=0;
	bool matchFound=false;

	uint8_t* tempPtr = NULL;
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

 	// Save return value of allocated data for user
 	rtnPtr = (void*) (g_allocation_ptrs[index] + sizeof(uint8_t*));

 	// Update allocation pointer to next free element
 	memcpy(&tempPtr, &g_allocation_ptrs[index], sizeof(uint8_t*));

 	// Adjust to point to meta data (next block pointer)
 	tempPtr -= sizeof(uint8_t*);
 	memcpy(&g_allocation_ptrs[index], &tempPtr, sizeof(uint8_t*));

 	return rtnPtr;
}

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
			printf("Pointer found in zone %u", index); // DEBUG remove later
			matchFound = true;
			break;
		}
	}

	if(matchFound == false)
	{
		printf("Warning: call to pool free was with a pointer not in pool heap\n");
		return;
	}

	// Set allocation pointer to the zone being freed, and set next pointer to previously free block
	memcpy(&tempPtr, &g_allocation_ptrs[index], sizeof(uint8_t*));

	ptr -= sizeof(uint8_t*);
	g_allocation_ptrs[index] = ptr;

	memcpy(&g_allocation_ptrs[index], &tempPtr, sizeof(uint8_t*));

}

void* pool_malloc_OLD(size_t n) 
{ 
	bool matchFound = false;
	bool emptyBlockFound = false;

	uint8_t* ptr;
	uint16_t cnt;
	uint32_t jump=0; // DEBUG remove later
	uint32_t index=0;

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

 	// TODO: Verify sectioned block is free??? We could track it, think about it (idea)
 	ptr = g_pool_heap;

 	// TODO: Could simplify this into one expression
 	jump = (uint32_t)SIZE_OF_GLOBAL_HEAP_BYTES;
 	jump = jump / ((uint32_t)g_block_size_count);
 	jump *= index;

 	// Jump to the right sector for allocation sizes
 	ptr += jump;

 	cnt = 0; // DEBUG TODO remove later

 	while(emptyBlockFound == false)
 	{
 		if(*ptr == 0)
 		{
 			printf("Free block found, at position %d!\n", cnt);
 			emptyBlockFound = true;
 			*ptr = 0x01;
 			break;
 		}
 		else
 		{
 			if( (ptr+1+n) < &g_pool_heap[SIZE_OF_GLOBAL_HEAP_BYTES-1] )
 			{
 				ptr += n+1; //+1 for meta data with each block
 				cnt++;
 			}
 			else
 			{
 				// We have reached the end of the heap
 				break;
 			}
 		}
 	}

 	if(emptyBlockFound == false)
 	{
 		return NULL;
 	}
 	else
 	{
 		return (void*) ptr+1; // +1 to get pass memory excluding meta data
 	}
} 

void pool_free_OLD(void* ptr) 
{ 
	uint8_t* blockMetaPtr;

	// Verify the ptr is not NULL
	if(ptr == NULL)
	{
		printf("Warning: NULL pointer passed to free\n");
		return;
	}

	// Point to block meta data, and mark as available
	blockMetaPtr = (uint8_t*) --ptr;

	// Sanity check this is a valid meta data pointer value
	if(*blockMetaPtr != 1)
	{
		printf("Warning: Attempting to freeing a pointer to pool that has invalid meta data\n");
		return;
	}

	*blockMetaPtr = 0x00;

	ptr = NULL;
}

void pool_test(void)
{
	const size_t block_sizes[2] = {8, 16};
	size_t block_size_count = 2;

	// testArray* arr1;
	// testArray* arr2;
	// uint32_t* arr3;

	pool_init(block_sizes, block_size_count);
	pool_malloc(8);

	//pool_print_block_info(0,100);
	//pool_print_block_info((uint32_t)SIZE_OF_GLOBAL_HEAP_BYTES / 2,100);

	// arr1 = (testArray*) pool_malloc(sizeof(testArray));
	// arr2 = (testArray*) pool_malloc(sizeof(testArray));
	// arr2 = (testArray*) pool_malloc(sizeof(testArray));
	// arr2 = (testArray*) pool_malloc(sizeof(testArray));

	// pool_free(arr2);
	// pool_free(arr2);
	// pool_free(arr1);

	// arr1 = (testArray*) pool_malloc(sizeof(testArray));
	// arr2 = (testArray*) pool_malloc(sizeof(testArray));
	// arr1 = (testArray*) pool_malloc(sizeof(testArray));
	// arr1 = (testArray*) pool_malloc(sizeof(testArray));

	// arr3 = (uint32_t*) pool_malloc(5*sizeof(uint32_t));
	// arr3 = (uint32_t*) pool_malloc(5*sizeof(uint32_t));
	// arr3 = (uint32_t*) pool_malloc(5*sizeof(uint32_t));
	// arr3 = (uint32_t*) pool_malloc(5*sizeof(uint32_t));
	// arr3 = (uint32_t*) pool_malloc(5*sizeof(uint32_t));

	// pool_free(arr3);

	// arr3 = (uint32_t*) pool_malloc(5*sizeof(uint32_t));
}

// Private Functions
static void pool_print_block_info(uint32_t start, uint32_t length)
{
	for(uint32_t i=0;i<length;i++)
	{
		printf("0x%02X: 0x%02X\n", i+start, g_pool_heap[i+start]);	
	}
}
