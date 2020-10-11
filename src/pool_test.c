#include "pool_test.h"

/////////////////// Test 1: Able to initialize up to max block zone amount
/////////////////// Test 2: pool_init fails with too many bock sizes
/////////////////// Test 3: Malloc returns pointer with single block
/////////////////// Test 4: Malloc returns valid pointers with multiple block sizes
/////////////////// Test 5: Malloc returns valid pointer with max block sizes
/////////////////// Test 6: Single block size able to allocate full heap
/////////////////// Test 7: Single block size handles trying to overrun heap
/////////////////// Test 8: Single block size able to fully allocate/free/allocate
/////////////////// Test 9: Multiple block sizes able to allocate full heap
/////////////////// Test 10: Multiple block sizes handles trying to overrun heap
/////////////////// Test 11: Multiple block sizes able to fully allocate/free/allocate
/////////////////// Test 12: Max block sizes able to allocate full heap
/////////////////// Test 13: Multiple block size handles trying to overrun heap for each zone
/////////////////// Test 14: Max block sizes able to fully allocate/free/allocate

void pool_test(void)
{
	uint8_t* testPtrs[4096];
	size_t testBlockSizes[MAX_BLOCK_SIZES];
	bool testFail = false;
	uint32_t numBlocksInZone[MAX_BLOCK_SIZES];
	size_t testTotalBlocks;
	size_t i,j,k;

	/////////////////// Test 1: Able to initialize up to max block zone amount
	printf("Test 1: Able to initialize up to max block zone amount\n");
	// Setup
	testFail = false;
	for(i=0;i<MAX_BLOCK_SIZES;i++)
	{
		testBlockSizes[i] = (i+1)*8;
	}

	// Test
	for(i=1;i<MAX_BLOCK_SIZES+1;i++)
	{
		if(pool_init(testBlockSizes, i) == false)
		{
			testFail = true;
			break;
		}
	}

	if(testFail == true)
	{
		printf("Test 1 failed!\n");
	}
	else 
	{
		printf("Test 1 passed!\n");
	}

	/////////////////// Test 2: pool_init fails with too many bock sizes
	printf("Test 2: pool_init fails with too many bock sizes\n");
	// Setup
	testFail = false;
	for(i=0;i<MAX_BLOCK_SIZES;i++)
	{
		testBlockSizes[i] = (i+1)*8;
	}
	memset(testPtrs, 0x00, sizeof(testPtrs));

	// Test
	if(pool_init(testBlockSizes, MAX_BLOCK_SIZES + 1) == true)
	{
		testFail = true;
	}

	if(testFail == true)
	{
		printf("Test 2 failed!\n");
	}
	else 
	{
		printf("Test 2 passed!\n");
	}

	/////////////////// Test 3: Malloc returns pointer with single block
	printf("Test 3: Malloc returns pointer with single block\n");
	// Setup
	testFail = false;
	for(i=0;i<MAX_BLOCK_SIZES;i++)
	{
		testBlockSizes[i] = (i+1)*8;
	}
	memset(testPtrs, 0x00, sizeof(testPtrs));

	// Test
	pool_init(testBlockSizes, 1);

	testPtrs[0] = (uint8_t*)pool_malloc(8);

	if(testPtrs[0] == NULL)
	{
		testFail = true;
	}

	if(testFail == true)
	{
		printf("Test 3 failed!\n");
	}
	else 
	{
		printf("Test 3 passed!\n");
	}

	/////////////////// Test 4: Malloc returns valid pointers with multiple block sizes
	printf("Test 4: Malloc returns valid pointers with multiple block sizes\n");
	// Setup
	testFail = false;
	for(i=0;i<MAX_BLOCK_SIZES;i++)
	{
		testBlockSizes[i] = (i+1)*8;
	}
	memset(testPtrs, 0x00, sizeof(testPtrs));

	// Test
	pool_init(testBlockSizes, 5);

	for(i=0;i<5;i++)
	{
		testPtrs[i] = (uint8_t*)pool_malloc((i+1)*8);
		if(testPtrs[i] == NULL)
		{
			testFail = true;
			break;
		}
	}

	if(testFail == true)
	{
		printf("Test 4 failed!\n");
	}
	else 
	{
		printf("Test 4 passed!\n");
	}

	/////////////////// Test 5: Malloc returns valid pointer with max block sizes
	printf("Test 5: Malloc returns valid pointer with max block sizes\n");
	// Setup
	testFail = false;
	for(i=0;i<MAX_BLOCK_SIZES;i++)
	{
		testBlockSizes[i] = (i+1)*8;
	}
	memset(testPtrs, 0x00, sizeof(testPtrs));

	// Test
	pool_init(testBlockSizes, MAX_BLOCK_SIZES);

	for(i=0;i<MAX_BLOCK_SIZES;i++)
	{
		testPtrs[i] = (uint8_t*)pool_malloc((i+1)*8);
		if(testPtrs[i] == NULL)
		{
			testFail = true;
			break;
		}
	}

	if(testFail == true)
	{
		printf("Test 5 failed!\n");
	}
	else 
	{
		printf("Test 5 passed!\n");
	}


	/////////////////// Test 6: Single block size able to allocate full heap
	printf("Test 6: Single block size able to allocate full heap\n");
	// Setup
	testFail = false;
	testTotalBlocks = 1;
	for(i=0;i<MAX_BLOCK_SIZES;i++)
	{
		testBlockSizes[i] = (i+1)*8;
		numBlocksInZone[i] = ((uint32_t)SIZE_OF_GLOBAL_HEAP_BYTES / (uint32_t)testTotalBlocks) / ((uint32_t) testBlockSizes[0] + sizeof(uint8_t*));
		testPtrs[i] = NULL;
	}
	memset(testPtrs, 0x00, sizeof(testPtrs));

	// Test
	pool_init(testBlockSizes, testTotalBlocks);

	for(i=0;i<numBlocksInZone[0];i++)
	{
		testPtrs[i] = (uint8_t*)pool_malloc(testBlockSizes[0]);

		if(testPtrs[i] == NULL)
		{
			testFail = true;
			break;
		}
	}
	
	if(testFail == true)
	{
		printf("Test 6 failed!\n");
	}
	else 
	{
		printf("Test 6 passed!\n");
	}

	/////////////////// Test 7: Single block size handles trying to overrun heap
	printf("Test 7: Single block size handles trying to overrun heap\n");
	// Setup
	testFail = false;
	testTotalBlocks = 1;
	for(i=0;i<MAX_BLOCK_SIZES;i++)
	{
		testBlockSizes[i] = (i+1)*8;
		numBlocksInZone[i] = ((uint32_t)SIZE_OF_GLOBAL_HEAP_BYTES / (uint32_t)testTotalBlocks) / ((uint32_t) testBlockSizes[0] + sizeof(uint8_t*));
	}
	memset(testPtrs, 0x00, sizeof(testPtrs));

	// Test
	pool_init(testBlockSizes, testTotalBlocks);

	for(i=0;i<numBlocksInZone[0];i++)
	{
		testPtrs[0] = (uint8_t*)pool_malloc(8);
	}

	testPtrs[0] = (uint8_t*)pool_malloc(8); // Should get a NULL returned here if allocation is full

	if(testPtrs[0] != NULL)
	{
		testFail = true;
	}
	
	if(testFail == true)
	{
		printf("Test 7 failed!\n");
	}
	else 
	{
		printf("Test 7 passed!\n");
	}

	/////////////////// Test 8: Single block size able to fully allocate/free/allocate
	printf("Test 8: Single block size able to fully allocate/free/allocate\n");
	// Setup
	testFail = false;
	testTotalBlocks = 1;
	for(i=0;i<MAX_BLOCK_SIZES;i++)
	{
		testBlockSizes[i] = (i+1)*8; // want to get 100 blocks
		numBlocksInZone[i] = ((uint32_t)SIZE_OF_GLOBAL_HEAP_BYTES / (uint32_t)testTotalBlocks) / ((uint32_t) testBlockSizes[0] + sizeof(uint8_t*));
		
	}

	memset(testPtrs, 0x00, sizeof(testPtrs));

	// Test
	pool_init(testBlockSizes, testTotalBlocks);

	for(i=0;i<numBlocksInZone[0];i++)
	{
		testPtrs[i] = (uint8_t*)pool_malloc(8);
	}

	for(i=0;i<numBlocksInZone[0];i++)
	{
		pool_free(testPtrs[i]);
	}

	for(i=0;i<numBlocksInZone[0];i++)
	{
		testPtrs[i] = (uint8_t*)pool_malloc(8);
		if(testPtrs[i] == NULL)
		{
			testFail = true;
			break;
		}
	}

	if(testFail == true)
	{
		printf("Test 8 failed!\n");
	}
	else 
	{
		printf("Test 8 passed!\n");
	}

	/////////////////// Test 9: Multiple block sizes able to allocate full heap
	printf("Test 9: Multiple block sizes able to allocate full heap\n");
	// Setup
	testFail = false;
	testTotalBlocks = 5;
	for(i=0;i<5;i++)
	{
		testBlockSizes[i] = (i+1)*8;
		numBlocksInZone[i] = ((uint32_t)SIZE_OF_GLOBAL_HEAP_BYTES / (uint32_t)testTotalBlocks) / ((uint32_t) testBlockSizes[i] + sizeof(uint8_t*));
		printf("Number of blocks in zone %u: %d, (data size = %u)\n", (unsigned int) i, numBlocksInZone[i], (unsigned int) testBlockSizes[i]);
	}

	memset(testPtrs, 0x00, sizeof(testPtrs));

	// Test
	pool_init(testBlockSizes, testTotalBlocks);

	for(i=0,k=0;i<5;i++)
	{
		for(j=0;j<numBlocksInZone[i];j++,k++)
		{
			testPtrs[k] = (uint8_t*) pool_malloc(testBlockSizes[i]);

			if(testPtrs[k] == NULL)
			{
				testFail = true;
				break;
			}
		}

		if(testFail == true)
		{
			break;
		}
	}
	
	if(testFail == true)
	{
		printf("Test 9 failed!\n");
	}
	else 
	{
		printf("Test 9 passed!\n");
	}

	/////////////////// Test 10: Multiple block sizes handles trying to overrun heap
	printf("Test 10: Multiple block sizes handles trying to overrun heap\n");
	// Setup
	testFail = false;
	testTotalBlocks = 5;
	for(i=0;i<5;i++)
	{
		testBlockSizes[i] = (i+1)*8;
		numBlocksInZone[i] = ((uint32_t)SIZE_OF_GLOBAL_HEAP_BYTES / (uint32_t)testTotalBlocks) / ((uint32_t) testBlockSizes[i] + sizeof(uint8_t*));
		printf("Number of blocks in zone %u: %d, (data size = %u)\n", (unsigned int) i, numBlocksInZone[i], (unsigned int) testBlockSizes[i]);
	}

	memset(testPtrs, 0x00, sizeof(testPtrs));

	// Test
	pool_init(testBlockSizes, testTotalBlocks);

	for(i=0,k=0;i<5;i++)
	{
		for(j=0;j<numBlocksInZone[i];j++,k++)
		{
			testPtrs[k] = (uint8_t*) pool_malloc(testBlockSizes[i]);

			if(testPtrs[k] == NULL)
			{
				testFail = true;
				break;
			}
		}

		if(testFail == true)
		{
			break;
		}
	}

	// Should get a NULL returned here for each block size
	for(i=0;i<5;i++)
	{
		testPtrs[i] = (uint8_t*)pool_malloc(testBlockSizes[i]);
		if(testPtrs[i] != NULL)
		{
			testFail = true;
			break;
		}
	}
	
	if(testFail == true)
	{
		printf("Test 10 failed!\n");
	}
	else 
	{
		printf("Test 10 passed!\n");
	}

	/////////////////// Test 11: Multiple block sizes able to fully allocate/free/allocate
	printf("Test 11: Multiple block sizes able to fully allocate/free/allocate\n");
	// Setup
	testFail = false;
	testTotalBlocks = 5;
	for(i=0;i<5;i++)
	{
		testBlockSizes[i] = (i+1)*8;
		numBlocksInZone[i] = ((uint32_t)SIZE_OF_GLOBAL_HEAP_BYTES / (uint32_t)testTotalBlocks) / ((uint32_t) testBlockSizes[i] + sizeof(uint8_t*));
		printf("Number of blocks in zone %u: %d, (data size = %u)\n", (unsigned int) i, numBlocksInZone[i], (unsigned int) testBlockSizes[i]);
	}

	memset(testPtrs, 0x00, sizeof(testPtrs));

	// Test
	pool_init(testBlockSizes, testTotalBlocks);

	for(i=0,k=0;i<5;i++)
	{
		for(j=0;j<numBlocksInZone[i];j++,k++)
		{
			testPtrs[k] = (uint8_t*) pool_malloc(testBlockSizes[i]); // Allocate all blocks
		}
	}

	for(i=0,k=0;i<5;i++)
	{
		for(j=0;j<numBlocksInZone[i];j++,k++)
		{
			pool_free(testPtrs[k]); // Free all blocks
		}
	}

	for(i=0,k=0;i<5;i++)
	{
		for(j=0;j<numBlocksInZone[i];j++,k++)
		{
			testPtrs[k] = (uint8_t*) pool_malloc(testBlockSizes[i]); // Again allocate all blocks

			if(testPtrs[k] == NULL)
			{
				testFail = true;
				break;
			}
		}

		if(testFail == true)
		{
			break;
		}
	}
	
	if(testFail == true)
	{
		printf("Test 11 failed!\n");
	}
	else 
	{
		printf("Test 11 passed!\n");
	}
	
	/////////////////// Test 12: Max block sizes able to allocate full heap
	printf("Test 12: Max block sizes able to allocate full heap\n");
	// Setup
	testFail = false;
	testTotalBlocks = MAX_BLOCK_SIZES;
	for(i=0;i<MAX_BLOCK_SIZES;i++)
	{
		testBlockSizes[i] = (i+1)*8;
		numBlocksInZone[i] = ((uint32_t)SIZE_OF_GLOBAL_HEAP_BYTES / (uint32_t)testTotalBlocks) / ((uint32_t) testBlockSizes[i] + sizeof(uint8_t*));
		printf("Number of blocks in zone %u: %d, (data size = %u)\n", (unsigned int) i, numBlocksInZone[i], (unsigned int) testBlockSizes[i]);
	}

	memset(testPtrs, 0x00, sizeof(testPtrs));

	// Test
	pool_init(testBlockSizes, testTotalBlocks);

	for(i=0,k=0;i<MAX_BLOCK_SIZES;i++)
	{
		for(j=0;j<numBlocksInZone[i];j++,k++)
		{
			testPtrs[k] = (uint8_t*) pool_malloc(testBlockSizes[i]);

			if(testPtrs[k] == NULL)
			{
				testFail = true;
				break;
			}
		}

		if(testFail == true)
		{
			break;
		}
	}
	
	if(testFail == true)
	{
		printf("Test 12 failed!\n");
	}
	else 
	{
		printf("Test 12 passed!\n");
	}

	//////////////////// Test 13: Multiple block size handles trying to overrun heap for each zone
	printf("Test 13: Max block sizes handles trying to overrun heap for each zone\n");
	// Setup
	testFail = false;
	testTotalBlocks = MAX_BLOCK_SIZES;
	for(i=0;i<MAX_BLOCK_SIZES;i++)
	{
		testBlockSizes[i] = (i+1)*8;
		numBlocksInZone[i] = ((uint32_t)SIZE_OF_GLOBAL_HEAP_BYTES / (uint32_t)testTotalBlocks) / ((uint32_t) testBlockSizes[i] + sizeof(uint8_t*));
		printf("Number of blocks in zone %u: %d, (data size = %u)\n", (unsigned int) i, numBlocksInZone[i], (unsigned int) testBlockSizes[i]);
	}

	memset(testPtrs, 0x00, sizeof(testPtrs));

	// Test
	pool_init(testBlockSizes, testTotalBlocks);

	for(i=0,k=0;i<MAX_BLOCK_SIZES;i++)
	{
		for(j=0;j<numBlocksInZone[i];j++,k++)
		{
			testPtrs[k] = (uint8_t*) pool_malloc(testBlockSizes[i]);

			if(testPtrs[k] == NULL)
			{
				testFail = true;
				break;
			}
		}

		if(testFail == true)
		{
			break;
		}
	}

	// Should get a NULL returned here for each block size
	for(i=0;i<MAX_BLOCK_SIZES;i++)
	{
		testPtrs[i] = (uint8_t*)pool_malloc(testBlockSizes[i]);
		if(testPtrs[i] != NULL)
		{
			testFail = true;
			break;
		}
	}
	
	if(testFail == true)
	{
		printf("Test 13 failed!\n");
	}
	else 
	{
		printf("Test 13 passed!\n");
	}

	/////////////////// Test 14: Max block sizes able to fully allocate/free/allocate
	printf("Test 14: Max block sizes able to fully allocate/free/allocate\n");
	// Setup
	testFail = false;
	testTotalBlocks = MAX_BLOCK_SIZES;
	for(i=0;i<MAX_BLOCK_SIZES;i++)
	{
		testBlockSizes[i] = (i+1)*8;
		numBlocksInZone[i] = ((uint32_t)SIZE_OF_GLOBAL_HEAP_BYTES / (uint32_t)testTotalBlocks) / ((uint32_t) testBlockSizes[i] + sizeof(uint8_t*));
		printf("Number of blocks in zone %u: %d, (data size = %u)\n", (unsigned int) i, numBlocksInZone[i], (unsigned int) testBlockSizes[i]);
	}

	memset(testPtrs, 0x00, sizeof(testPtrs));

	// Test
	pool_init(testBlockSizes, testTotalBlocks);

	for(i=0,k=0;i<MAX_BLOCK_SIZES;i++)
	{
		for(j=0;j<numBlocksInZone[i];j++,k++)
		{
			testPtrs[k] = (uint8_t*) pool_malloc(testBlockSizes[i]); // Allocate all blocks
		}
	}

	for(i=0,k=0;i<MAX_BLOCK_SIZES;i++)
	{
		for(j=0;j<numBlocksInZone[i];j++,k++)
		{
			pool_free(testPtrs[k]); // Free all blocks
		}
	}

	for(i=0,k=0;i<MAX_BLOCK_SIZES;i++)
	{
		for(j=0;j<numBlocksInZone[i];j++,k++)
		{
			testPtrs[k] = (uint8_t*) pool_malloc(testBlockSizes[i]); // Again allocate all blocks

			if(testPtrs[k] == NULL)
			{
				testFail = true;
				break;
			}
		}

		if(testFail == true)
		{
			break;
		}
	}
	
	if(testFail == true)
	{
		printf("Test 14 failed!\n");
	}
	else 
	{
		printf("Test 14 passed!\n");
	}
}