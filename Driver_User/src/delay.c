#include "delay.h"

static uint32_t Tick;

void Systick_Increase(void)
{
    Tick++;
}

uint32_t Get_Time(void)
{
    return Tick;
}

void Delay_ms(uint32_t Time_ms)
{
    uint32_t temp = Time_ms*500;
    for(uint32_t i = 0; i < temp; i++)
    {
        Delay_us(1);
    }

}

void Delay_us(uint32_t Time_us)
{
    Tick = 0;
    while(Tick < Time_us);
}