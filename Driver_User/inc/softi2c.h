#ifndef __SOFTI2C_H 
#define __SOFTI2C_H
#include "stm32f10x.h"

#define SCL_LOW()       GPIO_ResetBits(GPIO_I2C_PORT, GPIO_SCL_PIN)
#define SCL_HIGH()      GPIO_SetBits(GPIO_I2C_PORT, GPIO_SCL_PIN)
#define SDA_LOW()       GPIO_ResetBits(GPIO_I2C_PORT, GPIO_SDA_PIN)
#define SDA_HIGH()      GPIO_SetBits(GPIO_I2C_PORT, GPIO_SDA_PIN)


void SOFT_I2c_Init(void);

void SOFT_I2c_Start(void);

void SOFT_I2c_Stop(void);

void SOFT_I2c_Write(uint8_t data);

void SOFT_I2c_Write_Byte(uint8_t data);

uint8_t SOFT_I2c_Read(uint8_t reg);



#endif //__SOFTI2C_H