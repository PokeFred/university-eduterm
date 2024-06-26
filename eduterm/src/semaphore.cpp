#include <semaphore.h>

//Semaphore erstellen/initalisieren
static int init_semaphore( void ) {
    sem_t sem;
    sem_init( &sem, 0, 1 );
    return 0;
}

//Zugriff anfordern
static void semaphore_lock ( sem_t *lock ) {
    if ( lock != 0 ) {

        sem_trywait(lock);
    }
}

//Zugriff freigeben
static void semaphore_unlock ( sem_t *unlock ) {
    int value;
    sem_getvalue(unlock, &value);
    if( value != 1) {

        sem_post(unlock);
    }
}
