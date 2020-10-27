#include "pool_alloc.h"
#include <stdio.h> 
#include <stdint.h> 
#include <stdbool.h> 
#include <string.h>

void pool_test(void);

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
