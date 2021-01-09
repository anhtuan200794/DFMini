#include "stm32f10x.h"
#include "gpio.h"
#include "clock.h"
#include "define.h"
#include "delay.h"
#include "lcd.h"

int main(void)
{
    SystemInit();
    SysTick_Config(ONEUS);
    CLOCK_Config();
    GPIO_Config();


    while(1){
        GPIO_SetBits(GPIO_LED_PORT, GPIO_LED_PIN);
        Delay_ms(1000);
        GPIO_ResetBits(GPIO_LED_PORT, GPIO_LED_PIN);
        Delay_ms(1000);
        lcd_test();
    }
}









