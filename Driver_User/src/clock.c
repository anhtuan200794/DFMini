#include "clock.h"

void CLOCK_Config(void)
{
    /* GPIOD Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    /* GPIOA Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    /* GPIOB Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}