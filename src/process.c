#include <stdlib.h>
#include <stdio.h>
#include "process.h"

/* Global variables */
PCB_queue queue;

/**
 * @brief Initialize process queue
 * @return (void)
 */
void initialize_process_queue()
{
    PCB_queue queue = *(PCB_queue *)malloc(sizeof(struct PCB_queue));
    queue.count = 0;
    queue.last_id = -1;
    queue.first_node = NULL;
    queue.last_node = NULL;
}

/**
 * @brief Add PCB block to queue end
 * @param pcb pcb block
 * @return (void)
 */
void *add_pcb(PCB *pcb)
{
    queue.last_id++;            // Update last PCB id
    pcb->pid = queue.last_id;   // Asign id to PCB

    /* Create PCB node */
    PCB_node *node = (PCB_node *)malloc(sizeof(PCB_node));
    node->pcb = pcb;
    node->next_reference = NULL;

    if (queue.first_node == NULL)
        queue.first_node = node;

    /* Update last node reference to new node */
    if (queue.last_node == NULL)
        queue.last_node = node;
    else
        queue.last_node->next_reference = node;

    /* Update last node with new node */
    queue.last_node = node;
    queue.count++;
}

/**
 * @brief Show all PCB block ids in queue
 * @return (void)
 */
void *show_queue()
{
    PCB_node *node = queue.first_node;

    while (node != NULL) {
        printf("PID: %ld \n", node->pcb->pid);
        node = node->next_reference;
    }
}

/**
 * @brief Generate PCB blocks and add to queue end
 * @return (void)
 */
void *process_generator(void *args)
{
    /* Keep thread alive with infinite loop */
    while (1) {
        sem_wait(&process_generator_sem);       // Wait for semaphore signal to continue

        /* Create dummy PCB and add to queue */
        PCB *pcb = (PCB *)malloc(sizeof(PCB));
        pcb->next_reference = NULL;
        add_pcb(pcb);
        show_queue();
    }
}