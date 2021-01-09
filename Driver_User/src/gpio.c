#include "gpio.h"
#include "stm32f10x_gpio.h"
#include "define.h"


void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_DeInit(GPIOA);
    GPIO_DeInit(GPIOB);
    GPIO_DeInit(GPIOC);
    
    /* Configure PB12 in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = GPIO_LED_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_LED_PORT, &GPIO_InitStructure);
    GPIO_SetBits(GPIO_LED_PORT, GPIO_LED_PIN);

    /* Configure PA4-7 for LCD*/
    GPIO_InitTypeDef GPIO_InitStruct_LCD;       //GIPOA4~7   
   
    GPIO_InitStruct_LCD.GPIO_Pin    = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;   
    GPIO_InitStruct_LCD.GPIO_Mode   = GPIO_Mode_Out_PP;   
    GPIO_InitStruct_LCD.GPIO_Speed  = GPIO_Speed_50MHz;    
    GPIO_Init(GPIOA,&GPIO_InitStruct_LCD);   

}