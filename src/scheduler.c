#include "scheduler.h"

/**
 * @brief Scheduler
 * @return (void)
 */
void* scheduler(void *args) 
{
    /* Keep thread alive with infinite loop */
    while (1) {
        sem_wait(&scheduler_sem);
        printf("Scheduler running \n");
    }
}