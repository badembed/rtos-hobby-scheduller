#include "rtos.h"
#include <stdint.h>

void task_create(task_param_init *task_param,
                 void (*task_func) (void *param),
                 void *param,
                 uint8_t task_priority,
                 uint32_t *task_stk_start,
                 uint32_t task_stk_size);

void task_move_tail_queue_priority(void);
void task_sleep(uint32_t timeout);
void task_exit(void);

