#ifndef PROCESS_H
#define PROCESS_H
#include "globals.h"

void initialize_process_queue();
void* add_pcb(PCB* pcb);
void* show_queue();
void* process_generator(void *args);

#endif