#include "hardspi.h"
#include "define.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"



// This function Init SPI mode
void SPI_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;
    // Clock config
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    
    // Gpio config
    GPIO_InitStructure.GPIO_Pin = GPIO_SPI1_PIN_CLK|GPIO_SPI1_PIN_MOSI;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIO_SPI1_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_SPI1_PIN_SS;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_SPI1_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_SPI1_PIN_MISO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIO_SPI1_PORT, &GPIO_InitStructure);

    // Spi mode config
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);
    SPI_Cmd(SPI1, ENABLE);
}

// This function accepts one byte
uint8_t SPI_Transmit_Receive_Byte(uint8_t Byte_Tx)
{
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI1, (uint16_t)Byte_Tx);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    return (uint8_t)SPI1->DR;
}

// This function tranfers a string
void SPI_Transmit_String(uint8_t* Buf)
{
    for(uint16_t i = 0; Buf[i] != 0; i++)
    {
        SPI_Transmit_Receive_Byte(Buf[i]);
    }
}