#ifndef __DEFINE_H

#define __DEFINE_H
#include "stm32f10x.h"

// Define Systemtick

#define ONEMS 72000
#define ONEUS 72

// Define ADDRESS I2c
#define ADDRESS_SLAVE 0x08

// Define pin led
#define GPIO_LED_PIN                       GPIO_Pin_13
#define GPIO_LED_PORT                      GPIOC

// Defien pin spi
#define GPIO_SS_PIN                        GPIO_Pin_0
#define GPIO_SCK_PIN                       GPIO_Pin_1
#define GPIO_MOSI_PIN                      GPIO_Pin_2
#define GPIO_MISO_PIN                      GPIO_Pin_3
#define GPIO_MASTER_PIN                    GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2
#define GPIO_SPI_PORT                      GPIOA

#define GPIO_SPI1_PIN_SS                    GPIO_Pin_4
#define GPIO_SPI1_PIN_CLK                   GPIO_Pin_5
#define GPIO_SPI1_PIN_MOSI                  GPIO_Pin_7
#define GPIO_SPI1_PIN_MISO                  GPIO_Pin_6
#define GPIO_SPI1_PORT                      GPIOA

// Define pin i2c
#define GPIO_SCL_PIN GPIO_Pin_8
#define GPIO_SDA_PIN GPIO_Pin_9
#define GPIO_I2C_PORT GPIOB

#endif // __DEFINE_H