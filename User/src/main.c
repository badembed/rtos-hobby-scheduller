#include "main.h"

#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_l3gd20.h"

#include "rtos.h"
#include "rtos_port.h"

int main(void)
{
    arm_disable_interrupts();

    /* Init interrupt for schedulling */
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/1000);

    /* Init and Test LCD */
    LCD_Init();
    LCD_LayerInit();

    LTDC_Cmd(ENABLE);

    LCD_SetLayer(LCD_FOREGROUND_LAYER);
    LCD_Clear(LCD_COLOR_BLACK);
    LCD_SetBackColor(LCD_COLOR_BLACK);
    LCD_SetTextColor(LCD_COLOR_WHITE);
    LCD_SetFont(&Font8x12);

    LCD_DisplayStringLine(LCD_LINE_2,
                          (uint8_t *)" The BADEMBED generation ");


    /* Run RTOS */
    start_rtos();

    /* Shouldn't get here */
    while(1) {};
}

