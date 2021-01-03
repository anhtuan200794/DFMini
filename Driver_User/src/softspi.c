#include "softspi.h"
#include "stm32f10x_gpio.h"
#include "define.h"
#include "delay.h"

/***************************************************************************************************
****************************************************************************************************
 * I/P Arguments: byte send
 * Return value  : byte receive
 * description  : This func is used to send and receive byte
***************************************************************************************************/
uint8_t SOFT_Spi_Write_Read(uint8_t data)
{
    SS_LOW();
    for(uint8_t i = 0; i < 8; i++)
    {
        if((data & 0x80) == 0x80)
        {
            MOSI_HIGH();
        }else
        {
            MOSI_LOW();
        }
        SCK_HIGH();
        data <<= 1;
        Delay_us(1);
        if(GPIO_ReadInputDataBit(GPIO_SPI_PORT, GPIO_MISO_PIN) == SET)
        {
            data |= 0x01;
        }
        SCK_LOW();
    }
    SS_HIGH();
    return data;
}
