#ifndef __DEFINE_H

#define __DEFINE_H
#include "stm32f10x.h"

// Define Systemtick

#define ONEMS 72000
#define ONEUS 72

// Define ADDRESS I2c
#define ADDRESS_SLAVE 0x08

// Define pin led
#define GPIO_LED_PIN                       GPIO_Pin_12
#define GPIO_LED_PORT                      GPIOB

// Define LCD pin
#define HT1621_CS   GPIO_Pin_4
#define HT1621_RD   GPIO_Pin_5
#define HT1621_WR   GPIO_Pin_6
#define HT1621_DAT  GPIO_Pin_7
#define LCD_PORT    GPIOA

#endif // __DEFINE_H