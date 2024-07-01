#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <semaphore.h>

/**
 * initialize the semaphore
 * @return int
 */
static int init_semaphore();

/**
 * lock the semaphore
 * @param sem_t sem
 * @return void
 */
static void semaphore_lock(sem_t sem);

/**
 * unlock the semaphore
 * @param sem_t sem
 * @return void
 */
static void semaphore_unlock(sem_t sem);

#endif
