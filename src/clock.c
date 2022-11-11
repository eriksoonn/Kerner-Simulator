#include "clock.h"

/**
 * @brief Generate clock signals and pass control to timers (one by one)
 * @return (void)
 */
void* initialize_clock(void *args) 
{
    while (1) {
        pthread_mutex_lock(&clock_mutex);                   // Lock mutex

        /* Give and retrive control to al timers (one by one) */
        while (done < 1) {
            pthread_cond_wait(&condition_1, &clock_mutex);  // Wait for timer to retrice control
        }

        done = 0;                                           // Reset finished timer count
        pthread_cond_broadcast(&condition_2);               // Broadcast signal to all timers
        pthread_mutex_unlock(&clock_mutex);                 // Unlock mutex
    }
}