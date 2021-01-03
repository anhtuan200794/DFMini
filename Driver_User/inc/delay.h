#ifndef __DELAY_H

#define __DELAY_H

#include "stm32f10x.h"

void Systick_Increase(void);

uint32_t Get_Time(void);

void Delay_ms(uint32_t Time_ms);

void Delay_us(uint32_t Time_us);

#endif // __DELAY_H