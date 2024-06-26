#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H

#include <semaphore.h>

shmcontent *getSharedMemory();

shmcontent *initSharedMemory();

void detachSharedMemory (shmcontent *addr);



#endif
