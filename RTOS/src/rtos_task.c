#include "rtos_task.h"
#include "rtos_port.h"
#include "rtos_func.h"
#include "rtos.h"
#include "user_func.h"

void task_create(task_param_init *task_param,
                 void (*task_func) (void *param),
                 void *param,
                 uint8_t task_priority,
                 uint32_t *task_stk_start,
                 uint32_t task_stk_size)
{
    uint32_t i;

    task_param->task_func = (void*)task_func;
    task_param->task_func_param = param;
    task_param->task_priority = task_priority;
    task_param->stk_start = (uint32_t*)&task_stk_start[task_stk_size - 1];

    task_param->stk_size = task_stk_size;
    task_stk_start = task_param->stk_start;

    for(i = 0; i < task_stk_size; i++)
    {
        *task_stk_start = 0xFFFFFFFF;
        task_stk_start--;
    }

    task_param->stk_top = tn_stack_init(task_param->task_func,
                                        task_param->stk_start,
                                        task_param->task_func_param);
    queue_task_add(task_param);
}

void task_move_tail_queue_priority(void)
{
    uint8_t priority;

    arm_disable_interrupts();

    queue_remove_task(&(curr_run_task->task_queue));
    queue_task_add(curr_run_task);

    priority = queue_find_priority_next_task();
    next_task_to_run = task_param_from_task_queue(task_queue_priority[priority].next);

    switch_context();

    arm_enable_interrupts();
}

void task_exit(void)
{
    uint8_t priority;

    arm_disable_interrupts();

    queue_remove_task(&(curr_run_task->task_queue));

    priority = queue_find_priority_next_task();
    next_task_to_run = task_param_from_task_queue(task_queue_priority[priority].next);

    switch_context();

    arm_enable_interrupts();
}

void task_sleep(uint32_t timeout)
{
    uint8_t priority;

    arm_disable_interrupts();

    queue_remove_task(&(curr_run_task->task_queue));
    queue_timeout_add(curr_run_task);
    curr_run_task->wakeup_count = timeout;

    priority = queue_find_priority_next_task();
    next_task_to_run = task_param_from_task_queue(task_queue_priority[priority].next);

    switch_context();
    arm_enable_interrupts();
}

