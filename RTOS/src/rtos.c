#include "rtos_task.h"
#include "rtos_port.h"
#include "rtos_func.h"
#include "rtos.h"
#include "user_func.h"

align_attr_start unsigned int timer_task_stack[128] align_attr_end;
task_param_init timer_task;
void timer_task_func(void *par);

align_attr_start unsigned int idle_task_stack[128] align_attr_end;
task_param_init idle_task;
void idle_task_func(void *par);

link_init task_queue_priority[NUM_PRIORITY];
link_init task_queue_timeout;

volatile int system_state;

task_param_init *next_task_to_run;
task_param_init *curr_run_task;

void start_rtos(void)
{
    uint8_t i;

    for(i = 0; i < NUM_PRIORITY; i++)
    {
        reset_queue_priority(i);
    }
    reset_queue_timeout();

    task_create(&timer_task,
                timer_task_func,
                NULL,
                0,
                &timer_task_stack[0],
                128);

    task_create(&idle_task,
                idle_task_func,
                NULL,
                31,
                &idle_task_stack[0],
                128);

    start_user_tasks();

    curr_run_task = &timer_task;
    next_task_to_run = &idle_task;

    start_exe();
}

void timer_task_func(void *par)
{
    uint8_t priority;
    task_param_init *task_temp;
    link_init *link_temp;

    while(1)
    {
        arm_disable_interrupts();

        link_temp = &(task_queue_timeout);
        while(link_temp->next != link_temp)
        {
            task_temp = task_param_from_task_queue(link_temp->next);
            link_temp = link_temp->next;

            task_temp->wakeup_count--;
            if(task_temp->wakeup_count == 0)
            {
                queue_remove_task(&(task_temp->task_queue));
                queue_task_add(task_temp);
            }
        }
        priority = queue_find_priority_next_task();
        next_task_to_run = task_param_from_task_queue(task_queue_priority[priority].next);

        switch_context();
        arm_enable_interrupts();
    }
}

void idle_task_func(void *par)
{
    while(1)
    {
    }
}

void rtos_tick(void)
{
    next_task_to_run = &timer_task;
}

void schedule_tick()
{
    rtos_tick();
    switch_context();
}

