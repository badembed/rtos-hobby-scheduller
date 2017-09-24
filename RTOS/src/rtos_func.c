#include "rtos_func.h"

void queue_task_add(task_param_init* task)
{
    link_init *temp_link;

    temp_link = &task_queue_priority[task->task_priority];
    while((*temp_link).next != temp_link)
    {
        temp_link = temp_link->next;
    }

    temp_link->next = &(task->task_queue);
    task->task_queue.prev = temp_link;
    task->task_queue.next = &task->task_queue; 
}

task_param_init * task_param_from_task_queue(link_init *queue)
{
    uint8_t *byte_offset;
    task_param_init *task;

    byte_offset = (uint8_t*)(&((task_param_init*)0)->task_queue);
    task = (task_param_init*)((uint8_t*)(queue) - byte_offset);

    return(task);
}

void reset_queue_priority(uint8_t priority)
{
    task_queue_priority[priority].next = &task_queue_priority[priority];
    task_queue_priority[priority].prev = &task_queue_priority[priority];
}

void queue_remove_task(link_init *task_queue)
{
    if(task_queue->next == task_queue)
    {
        task_queue->prev->next = task_queue->prev;
    }
    else
    {
        task_queue->prev->next = task_queue->next;
    }
    task_queue->next->prev = task_queue->prev;
}

unsigned int * tn_stack_init(void * task_func,
                             void * stack_start,
                             void * param)
{
    unsigned int * stk;

    stk  = (unsigned int *)stack_start;       //-- Load stack pointer

    *stk = 0x01000000L;                       //-- xPSR
    stk--;

    *stk = ((unsigned int)task_func) | 1;     //-- Entry Point (1 for THUMB mode)
    stk--;

    //*stk = ((unsigned int)tn_task_exit) | 1;  //-- R14 (LR)    (1 for THUMB mode)
    *stk = 0x14141414L;                       //-- R14
    stk--;

    *stk = 0x12121212L;                       //-- R12
    stk--;

    *stk = 0x03030303L;                       //-- R3
    stk--;

    *stk = 0x02020202L;                       //-- R2
    stk--;

    *stk = 0x01010101L;                       //-- R1
    stk--;

    *stk = (unsigned int)param;               //-- R0 - task's function argument
    stk--;

    *stk = 0x11111111L;                       //-- R11
    stk--;

    *stk = 0x10101010L;                       //-- R10
    stk--;

    *stk = 0x09090909L;                       //-- R9
    stk--;

    *stk = 0x08080808L;                       //-- R8
    stk--;

    *stk = 0x07070707L;                       //-- R7
    stk--;

    *stk = 0x06060606L;                       //-- R6
    stk--;

    *stk = 0x05050505L;                       //-- R5
    stk--;

    *stk = 0x04040404L;                       //-- R4

    return stk;
}

uint8_t queue_find_priority_next_task(void)
{
    uint8_t i;

    for(i = 1; i < NUM_PRIORITY; i++)
    {
        if(task_queue_priority[i].next != &(task_queue_priority[i]))
        {
            break;
        }
    }

    return(i);
}

void reset_queue_timeout(void)
{
    task_queue_timeout.next = &task_queue_timeout;
    task_queue_timeout.prev = &task_queue_timeout;
}

void queue_timeout_add(task_param_init* task)
{
    link_init *temp_link;

    temp_link = &task_queue_timeout;
    while((*temp_link).next != temp_link)
    {
        temp_link = temp_link->next;
    }
    temp_link->next = &(task->task_queue);
    task->task_queue.prev = temp_link;
    task->task_queue.next = &task->task_queue;
}

