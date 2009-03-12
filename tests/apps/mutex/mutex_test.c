/****************************************************
 * This is a test that will test mutexes            *
 ****************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

#include "carbon_user.h"
#include "sync_api.h"
#include "capi.h"

carbon_mutex_t my_mux;

// Functions executed by threads
void* test_mutex(void * threadid);

int main(int argc, char* argv[])  // main begins
{
   const unsigned int num_threads = 1;
   carbon_thread_t threads[num_threads];

   for(unsigned int i = 0; i < num_threads; i++)
       threads[i] = CarbonSpawnThread(test_mutex, (void *) i);

   for(unsigned int i = 0; i < num_threads; i++)
       CarbonJoinThread(threads[i]);

   printf("Finished running mutex test!.\n");

   return 0;
} // main ends


void* test_mutex(void *threadid)
{
   mutexInit(&my_mux);
   mutexLock(&my_mux);
   mutexUnlock(&my_mux);

   return NULL;
}

