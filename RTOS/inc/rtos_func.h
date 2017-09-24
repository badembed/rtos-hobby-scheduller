#include "rtos.h"
#include <stdint.h>

void reset_queue_priority(uint8_t priority);
void queue_task_add(task_param_init* task);
void queue_remove_task(link_init *task_queue);
void reset_queue_priority(uint8_t priority);
unsigned int * tn_stack_init(void * task_func,
                             void * stack_start,
                             void * param);
void reset_queue_timeout(void);
void reset_queue_sem(link_init *link_sem);
void queue_timeout_add(task_param_init* task);
task_param_init * task_param_from_task_queue(link_init *queue);
uint8_t queue_find_priority_next_task(void);
void queue_sem_add(task_param_init *task, sem_param_init *sem);


