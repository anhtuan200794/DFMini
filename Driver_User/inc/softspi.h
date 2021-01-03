#ifndef __SOFTSPI_H

#define __SOFTSPI_H
#include "stm32f10x.h"

#define SS_HIGH() GPIO_SetBits(GPIO_SPI_PORT, GPIO_SS_PIN)
#define SS_LOW() GPIO_ResetBits(GPIO_SPI_PORT, GPIO_SS_PIN)
#define SCK_HIGH() GPIO_SetBits(GPIO_SPI_PORT, GPIO_SCK_PIN)
#define SCK_LOW() GPIO_ResetBits(GPIO_SPI_PORT, GPIO_SCK_PIN)
#define MOSI_HIGH() GPIO_SetBits(GPIO_SPI_PORT, GPIO_MOSI_PIN)
#define MOSI_LOW() GPIO_ResetBits(GPIO_SPI_PORT, GPIO_MOSI_PIN)

uint8_t SOFT_Spi_Write_Read(uint8_t data);

#endif //__SOFTSPI_H