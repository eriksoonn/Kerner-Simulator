#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h> 
#include "globals.h"
#include "clock.h"
#include "timer.h"
#include "scheduler.h"
#include "process.h"

/* Global variables */
int done, scheduler_period, proccess_generator_period;
pthread_cond_t condition_1, condition_2 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t clock_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t scheduler_sem, process_generator_sem;

int main(int argc, char* const argv[])
{
    /* Define default parameters */
    unsigned int cpus = 1, cores = 2, threads = 2;
    scheduler_period = 10000, proccess_generator_period = 10000;
    pthread_mutex_t clock_mutex;

    /* Read user given parameters */
    int options;
    while ((options = getopt(argc, argv, "c:r:t:")) != -1) 
    {
        switch (options)
        {
        case 'c':
            cpus = atoi(optarg);
            break;
        case 'r':
            cores = atoi(optarg);
            break;
        case 't':
            threads = atoi(optarg);
            break;
        
        default:
            break;
        }
    }

    /* Initialize semaphores */
    sem_init(&scheduler_sem, 0, 0);
    sem_init(&process_generator_sem, 0, 0);

    /* Generate process queue */
    initialize_process_queue();

    /* Create threads */
    pthread_t scheduler_th, clock_th, timer_th, timer_th2, process_generator_th;

    /* Construct timer options structure */
    struct timer_options *scheduler_timer = (struct timer_options *)malloc(sizeof(struct timer_options));
    struct timer_options *proccess_gen_timer = (struct timer_options *)malloc(sizeof(struct timer_options));
    *scheduler_timer = (timer_options) {.semaphore = &scheduler_sem, .period = scheduler_period};
    *proccess_gen_timer = (timer_options) {.semaphore = &process_generator_sem, .period = proccess_generator_period};

    /* Initialize threads */
    pthread_create(&scheduler_th, NULL, &scheduler, NULL);
    pthread_create(&clock_th, NULL, &initialize_clock, NULL);
    pthread_create(&timer_th, NULL, &initialize_timer, (void *)scheduler_timer);
    pthread_create(&timer_th2, NULL, &initialize_timer, (void *)proccess_gen_timer);
    pthread_create(&process_generator_th, NULL, &process_generator, NULL);

    /* Master clock */
    pthread_join(clock_th, NULL);
}