// Initialize the pool allocator with a set of block sizes appropriate  for this application. 
// Returns true on success, false on failure. 
bool pool_init(const size_t* block_sizes, size_t block_size_count); 
// Allocate n bytes. 
// Returns pointer to allocate memory on success, NULL on failure. 
void* pool_malloc(size_t n); 
// Release allocation pointed to by ptr. 
void pool_free(void* ptr); 

void pool_test(void);



typedef struct testArray
{
	uint8_t arr[32];
} testArray;


// Hint
// *you are allowed to put an upper limit on the maximum number of block sizes that the user is  allowed to specify at initialization time

// *You can also assume any reasonable subdivision of the total heap amongst the 
// different block sizes (e.g.  evenly divide the total heap by the number of block 
// sizes, or make an assumption that smaller allocations are more common and weight 
// the  partition accordingly, etc). // THIS IS A BIG ONE

// *You can, however, add state  variables in addition to the main heap buffer (but if they're unreasonably large, be prepared to defend your decisions!) 
// Please include your test cases in your submission. 

// *The prompt will force you to make assumptions about what the user might want;  we want to see reasonable assumptions that are made deliberately and are documented.

// *We would prefer to see a clean, meticulous approach  with simplifying assumptions, rather than a fancier solution implemented halfway

// *Efficiency in both space and time are important--we appreciate  if you document intentional tradeoffs you make affecting performance.

// *Comprehensive test cases are important. It’s nice if we can compile the  code and run it, but ideally by reviewing your test cases we will already know whether your implementation works or not. 


// Approach for the heap, 
// lets say we have 3 different sizes, 1 byte, 32 bytes, 1 KB
//Idea 1:
// - Split up evenly, for the entire heap for each size
// - Going to start with this can make more complex later if needed 
// 21 KB of each size
// - How are we going to track these boundaries?


// Assumptions:
// Only can allocate 1 of each, I think this is fine

// Potential improvements
// instead of a byte of meta data, could get space back by just using a bit vector
// can we align things perfectly to save as much data in the heap as possible?

// Tradeoffs:

// Test Cases