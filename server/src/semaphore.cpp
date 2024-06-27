#include "semaphore.h"

#include <semaphore.h>

/**
 * ddd
 * @return int
 */
static int init_semaphore() {
    sem_t sem;
    return sem_init(&sem, 0, 1);
}

/**
 * ddd
 * @param sem_t sem
 * @return void
 */
static void semaphore_lock(sem_t sem) {
    if (sem == 0) return;
    sem_trywait(&sem);
}

/**
 * ddd
 * @param sem_t sem
 * @return void
 */
static void semaphore_unlock(sem_t sem) {
    int value;
    sem_getvalue(&sem, &value);

    if (value == 1) return;
    sem_post(&sem);
}
