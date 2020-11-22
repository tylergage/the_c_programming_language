
#include "readers_writers.h"
#include <dispatch/dispatch.h>

/***************************************************************
 * Function Prototypes
 ***************************************************************/

static void read_protected(void);
static void write_protected(void);
static void resource_read(void);
static void resource_write(void);

/***************************************************************
 * Problem Description
 ***************************************************************

 There is a resource in our system that is accessed by many
 threads for both reading and writing. We wish to protect this
 resource from concurrent accesses that could corrupt data
 while allowing maximum resource utilization. Protect access to
 the resource such that the following conditions are met:

 1. Only one thread may write to the resource at a time.
 2. While any thread is writing, no threads may be reading.
 3. There is no limit on the number of concurrent reads.

 You may use any basic C types and any combination of mutexes,
 semaphores, and condition variables. In this system, these are
 defined as:

 MUTEX
 -----------------------
 init:
   static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

 usage:
   pthread_mutex_lock(&lock);
   pthread_mutex_unlock(&lock);

 SEMAPHORE
 -----------------------
 init:
   static sem_t sem;
   sem_init(&sem, 0, {count}); // {count} is the initial value
                               // Initialize in main()

 usage:
   sem_wait(&sem);
   sem_post(&sem);

 CONDITION VARIABLE
 -----------------------
 init:
   static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

 usage:
   pthread_cond_wait(&cond, &lock);
   pthread_cond_signal(&cond);
   pthread_cond_broadcast(&cond);

****************************************************************/

/***************************************************************
 * Candidate Code
 ***************************************************************/
// static sem_t* readSem;
// static sem_t writeSem;

dispatch_semaphore_t readSemaphore;
dispatch_semaphore_t writeSemaphore;

static atomic_int numReaders = 0;
static atomic_int writeActive = 0;

static void read_protected(void)
{

  if(writeActive)
  {
    dispatch_semaphore_wait(writeSemaphore, DISPATCH_TIME_FOREVER);
  }

  atomic_fetch_add(&numReaders, 1);
  resource_read();
  atomic_fetch_sub(&numReaders, 1);

  if(numReaders == 0)
  {
    dispatch_semaphore_signal(readSemaphore);
  }
}

static void write_protected(void)
{
  if(numReaders > 0)
  {
    dispatch_semaphore_wait(readSemaphore, DISPATCH_TIME_FOREVER);
  }

  atomic_fetch_add(&writeActive, 1);
  resource_write();
  atomic_fetch_sub(&writeActive, 1);

  dispatch_semaphore_signal(writeSemaphore);

}

/***************************************************************
 * Resource interface
 ***************************************************************/

static atomic_int readers;
static atomic_int writers;

static void resource_read(void)
{
  atomic_fetch_add(&readers, 1);
  sleep(rand()%2);
  printf("READ: readers: %d, writers: %d\n", readers, writers);
  atomic_fetch_sub(&readers, 1);
}

static void resource_write(void)
{
  atomic_fetch_add(&writers, 1);
  sleep(rand()%3);
  printf("WRITE: readers: %d, writers: %d\n", readers, writers);
  atomic_fetch_sub(&writers, 1);
}


/***************************************************************
 * Threads
 ***************************************************************/

static void *read_func(void *arg)
{
  for (int i = 0; i < 4; i++)
  {
    read_protected();
  }

  return NULL;
}


static void *write_func(void *arg)
{
  for (int i = 0; i < 1; i++)
  {
    write_protected();
  }

  return NULL;
}

#define NUM_READERS 10
#define NUM_WRITERS 5

void test_readers_writers(void) {

  pthread_t readers[NUM_READERS];
  pthread_t writers[NUM_WRITERS];

  // readSem = sem_open("READ", O_CREAT);
  // if(readSem == SEM_FAILED)
  // {
  //   printf("Read semaphore failed!!!\n");
  // }

  // writeSem = sem_open("WRITE", O_CREAT);
  // if(writeSem == SEM_FAILED)
  // {
  //   printf("Write semaphore failed!!!\n");
  // }

  readSemaphore  = dispatch_semaphore_create(0);
  writeSemaphore = dispatch_semaphore_create(0);

  for (int i = 0; i < NUM_READERS; i++) {
    pthread_create( &readers[i], NULL, read_func, NULL);
  }
  for (int i = 0; i < NUM_WRITERS; i++) {
    pthread_create( &writers[i], NULL, write_func, NULL);
  }

  for (int i = 0; i < NUM_WRITERS; i++) {
    pthread_join( writers[i], NULL);
  }
  for (int i = 0; i < NUM_READERS; i++) {
    pthread_join( readers[i], NULL);
  }
  
}

