#ifndef USER_API_H
#define USER_API_H

#include "capi.h"
#include "mcp_api.h"
#include "sync_api.h"

void carbonInit();
void carbonFinish();

void sharedMemThreadsInit();
void sharedMemThreadsFinish();

extern "C" 
{
    int getCoreCount();
    void sharedMemQuit();
    void* shmem_thread_func(void *);
}

#endif
