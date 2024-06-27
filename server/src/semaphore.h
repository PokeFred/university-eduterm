#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <semaphore.h>

/**
 * ddd
 * @return int
 */
static int init_semaphore();

/**
 * ddd
 * @param sem_t sem
 * @return void
 */
static void semaphore_lock(sem_t sem);

/**
 * ddd
 * @param sem_t sem
 * @return void
 */
static void semaphore_unlock(sem_t sem);

#endif
