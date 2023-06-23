#ifndef _GLOBALS_H
#define _GLOBALS_H
#include <pthread.h>
#include <semaphore.h>
#include <semaphore.h>
#include "types.h"

/* Global variables */
extern pthread_mutex_t clock_mutex;                     // Clock mutex 
extern pthread_cond_t condition_1, condition_2;         // Thread block conditions
extern sem_t scheduler_sem, process_generator_sem;      // Semaphore (scheduler and process generator)
extern int done;                                        // Finished timer number
extern int scheduler_period, proccess_generator_period; // Timer signar creation period
extern PCB_queue queue;                                 // PCB queue

#endif