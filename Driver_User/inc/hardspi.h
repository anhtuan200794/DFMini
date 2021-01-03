#ifndef __HARDSPI_H

#define __HARDSPI_H
#include "stm32f10x.h"


void SPI_Config(void);

uint8_t SPI_Transmit_Receive_Byte(uint8_t Byte_Tx);

void SPI_Transmit_String(uint8_t* Buf);

#endif //__HARDSPI_H