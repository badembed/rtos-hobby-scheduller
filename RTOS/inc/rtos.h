#include "rtos_param.h"
#include <stdint.h>

#ifndef H_MYRTOS
#define H_MYRTOS

typedef struct _link_init
{
    struct _link_init * prev;
    struct _link_init * next;
} link_init;

typedef struct _task_param_init
{
    uint32_t *stk_top;
    uint32_t *stk_start;
    uint32_t stk_size;
    uint8_t task_priority;
    uint32_t wakeup_count;
    link_init task_queue;
    void *task_func;
    void *task_func_param;
} task_param_init;

typedef struct _sem_param_init
{
    link_init sem_queue;
    uint8_t count;
    uint8_t max_count;
} sem_param_init;
#endif

extern link_init task_queue_priority[NUM_PRIORITY];
extern link_init task_queue_timeout;

extern volatile int rtos_system_state;
extern task_param_init *next_task_to_run;
extern task_param_init *curr_run_task;

void start_rtos(void);
void start_exe(void);
void rtos_tick(void);

