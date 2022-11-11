#include "timer.h"
#include <stdio.h>

/**
 * @brief Generate signal to thread, reduced from clock with given period
 * @param optios structure containing period and semaphore
 * @return (void)
 */
void* initialize_timer(void *optios) 
{
    /* Parameters */
    int period = ((struct timer_options*)optios)->period;           // Period to create semaphore signal
    sem_t* semaphore = ((struct timer_options*)optios)->semaphore;  // Semaphore

    int tick = 0;                       // Period counter
    pthread_mutex_lock(&clock_mutex);   // Lock mutex

    /* Keep thread alive with infinite loop */
    while (1) {
        done++;                                         // Increment finished timer counter
        tick++;

        /* Reduction from clock signal to process signal */
        if (tick > period) {
            sem_post(semaphore);                        // Send continue signal to other thread
            tick = 0;
        }

        pthread_cond_signal(&condition_1);
        pthread_cond_wait(&condition_2, &clock_mutex);  // Wait for clock signal to continue
    }
}