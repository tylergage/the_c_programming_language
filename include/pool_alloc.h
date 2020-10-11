#include <stdio.h> 
#include <stdint.h> 
#include <stdbool.h> 
#include <string.h>

// Initialize the pool allocator with a set of block sizes appropriate  for this application. 
#define MAX_BLOCK_SIZES 10
#define SIZE_OF_GLOBAL_HEAP_BYTES 65536

// Returns true on success, false on failure. 
bool pool_init(const size_t* block_sizes, size_t block_size_count); 
// Allocate n bytes. 
// Returns pointer to allocate memory on success, NULL on failure. 
void* pool_malloc(size_t n); 
// Release allocation pointed to by ptr. 
void pool_free(void* ptr); 

// Notes:
// *	Design implementation really took from this link:
//  	http://dmitrysoshnikov.com/compilers/writing-a-pool-allocator/
//		All code however is 100% created by myself, but yeah ripped off the design from that link lol
// 
// *	Started with a more brute force solution, allocating a single byte per block to mark
// 		if a block was free. Would have to iterate blocks, giving an O(N) solution. 
// 		After a Google search, found the above link and wanted to do that. 
//		It is certainly more efficient O(1), but you lose a little space in the heap. 

///////// Assumptions:
// all memory zones split up evenly, could optimize to give smaller sizes more maybe
// malloc only can allocate 1 block of each memory item at a time
// free is always passed correct pointer, not checking for that which is something that should be checked
// Pointer being returned in malloc, data is garbage and not initizlized

///////// Potential improvements:
// malloc, can further improve to use blocks of other sizes that are bigger than what was requested if it fills up
// free could be more robust, if wrong pointer is passed could screw up stack, should do checking
// can we align things perfectly to save as much data in the heap as possible?
// Probably more test cases I can think of ie, checking data is still valid after multiple malloc and frees called
