#ifndef _TYPES_H
#define _TYPES_H

/* PCB block */
typedef struct PCB 
{
    struct PCB* next_reference;         // Reference to next PCB structure
    long pid;                           // PCB id 
} PCB;  

/* PCB queue node */
typedef struct PCB_node
{
    PCB* pcb;                           // Reference to PCB block
    struct PCB_node* next_reference;    // Reference to next PCB noce structure
} PCB_node;

/* PCB queue */
typedef struct PCB_queue
{
    PCB_node* first_node;               // Reference to first PCB node
    PCB_node* last_node;                // Reference to last PCB node
    int count;                          // Number of node elements
    int last_id;                        // Last asigned PCB id
} PCB_queue;

/* Timer options capsule */
typedef struct timer_options 
{
    sem_t* semaphore;                   // Thread control semaphore
    int period;                         // Period to activate semaphore
} timer_options;

#endif