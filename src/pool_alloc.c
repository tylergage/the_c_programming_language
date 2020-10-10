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

static bool heap_initialized = false;

// I think we need a tracker for each block size to know next available block, right?

// Public Functions
bool pool_init(const size_t* block_sizes, size_t block_size_count) { 
	
	heap_initialized = false;
	
	// Check inputs
	if(block_size_count > MAX_BLOCK_SIZES)
	{
		return false;
	}

	// Save local file data for heap allocator
	g_block_size_count = block_size_count;

	for(size_t i=0; i < g_block_size_count; i++)
	{
		g_block_sizes[i] = block_sizes[i];
	}

	// Clear heap data
	memset(g_pool_heap, 0, SIZE_OF_GLOBAL_HEAP_BYTES);
	// ToDo: Free any pointer data or handle if this function is called twice?

	heap_initialized = true;


	return true;
} 

void* pool_malloc(size_t n) 
{ 
	bool matchFound = false;
	bool emptyBlockFound = false;

	uint8_t* ptr;
	uint16_t cnt;
	uint32_t jump=0; // DEBUG remove later
	uint32_t index=0;

 	// Check that n is a valid size, and find index in saved 
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

void pool_free(void* ptr) 
{ 
	uint8_t* blockMetaPtr;

	// Verify the ptr is not NULL
	if(ptr == NULL)
	{
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
	const size_t block_sizes[1] = {sizeof(testArray)};
	size_t block_size_count = 1;

	testArray* arr1;
	testArray* arr2;

	pool_init(block_sizes, block_size_count);

	arr1 = (testArray*) pool_malloc(sizeof(testArray));
	arr2 = (testArray*) pool_malloc(sizeof(testArray));
	arr2 = (testArray*) pool_malloc(sizeof(testArray));
	arr2 = (testArray*) pool_malloc(sizeof(testArray));

	pool_free(arr2);
	pool_free(arr2);
	pool_free(arr1);

	arr1 = (testArray*) pool_malloc(sizeof(testArray));
	arr2 = (testArray*) pool_malloc(sizeof(testArray));
	arr1 = (testArray*) pool_malloc(sizeof(testArray));
	arr1 = (testArray*) pool_malloc(sizeof(testArray));
}

// Private Functions
