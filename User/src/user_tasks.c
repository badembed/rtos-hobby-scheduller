#include "user_func.h"

#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_l3gd20.h"

align_attr_start unsigned int task_1_stack[128] align_attr_end;
task_param_init task_1;
void task_1_func(void *par);

align_attr_start unsigned int task_2_stack[128] align_attr_end;
task_param_init task_2;
void task_2_func(void *par);

sem_param_init sem_test;

void task_1_func(void *par)
{
    extern uint8_t g_flag;

    while(1) {
        LCD_ClearLine(LCD_LINE_4);
        LCD_DisplayStringLine(LCD_LINE_4,
                              (uint8_t *)" TASK 1 work ");
        task_sleep(2000);

        LCD_ClearLine(LCD_LINE_4);
        LCD_DisplayStringLine(LCD_LINE_4,
                              (uint8_t *)" TASK 1 sleep ");
        task_sleep(2000);
    }
}

void task_2_func(void *par)
{
    extern uint8_t g_flag;

    while(1)
    {
        LCD_ClearLine(LCD_LINE_5);
        LCD_DisplayStringLine(LCD_LINE_5,
                              (uint8_t *)" TASK 2 work ");
        task_sleep(2000);

        LCD_ClearLine(LCD_LINE_5);
        LCD_DisplayStringLine(LCD_LINE_5,
                              (uint8_t *)" TASK 2 sleep ");
        task_sleep(2000);
    }
}

void start_user_tasks(void)
{
    task_create(&task_1,
                task_1_func,
                NULL,
                1,
                &task_1_stack[0],
                128);

    task_create(&task_2,
                task_2_func,
                NULL,
                1,
                &task_2_stack[0],
                128);
}

