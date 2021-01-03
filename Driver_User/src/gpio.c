#include "gpio.h"
#include "stm32f10x_gpio.h"
#include "define.h"


void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_DeInit(GPIOA);
    GPIO_DeInit(GPIOB);
    GPIO_DeInit(GPIOC);
    
    /* Configure PC13 in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = GPIO_LED_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_LED_PORT, &GPIO_InitStructure);
    GPIO_SetBits(GPIO_LED_PORT, GPIO_LED_PIN);

    /* Configure PA0 as SS pin, 
    *  PA1 as SCK pin, 
    *  PA2 as MOSI pin, 
    *  PA3 as MISO pin
    */
    GPIO_InitStructure.GPIO_Pin = GPIO_MASTER_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_SPI_PORT, &GPIO_InitStructure);
    GPIO_SetBits(GPIO_SPI_PORT, GPIO_SS_PIN);
    GPIO_ResetBits(GPIO_SPI_PORT, GPIO_SCK_PIN);
    GPIO_ResetBits(GPIO_SPI_PORT, GPIO_MOSI_PIN);


    GPIO_InitStructure.GPIO_Pin = GPIO_MISO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIO_SPI_PORT, &GPIO_InitStructure);

    /*  Config PB3 as SCL pin,
    *   PB4 as SDA pin
    */
    GPIO_InitStructure.GPIO_Pin = GPIO_SCL_PIN|GPIO_SDA_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_I2C_PORT, &GPIO_InitStructure);


}