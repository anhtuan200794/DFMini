/* Includes ------------------------------------------------------------------*/
#include "w25qxx.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"
#include "delay.h"

void FLASH_DeInit(void)
{
    FLASH_LowLevel_DeInit();
}

/**
  * @brief  Initializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  */
void FLASH_Init(void)
{
    SPI_InitTypeDef  SPI_InitStructure;

    FLASH_LowLevel_Init();

    /*!< Deselect the FLASH: Chip Select high */
    FLASH_CS_HIGH();

    /*!< SPI configuration */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    /*!< Enable the sFLASH_SPI  */
    SPI_Cmd(SPI1, ENABLE);
}

/**
  * @brief  Erases the specified FLASH sector.
  * @param  SectorAddr: address of the sector to erase.
  * @retval None
  */
void FLASH_EraseSector(uint32_t SectorAddr)
{
    /*!< Send write enable instruction */
    FLASH_WriteEnable();

    /*!< Sector Erase */
    /*!< Select the FLASH: Chip Select low */
    FLASH_CS_LOW();
    /*!< Send Sector Erase instruction */
    FLASH_SendByte(FLASH_CMD_SE);
    /*!< Send SectorAddr high nibble address byte */
    FLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
    /*!< Send SectorAddr medium nibble address byte */
    FLASH_SendByte((SectorAddr & 0xFF00) >> 8);
    /*!< Send SectorAddr low nibble address byte */
    FLASH_SendByte(SectorAddr & 0xFF);
    /*!< Deselect the FLASH: Chip Select high */
    FLASH_CS_HIGH();

    /*!< Wait the end of Flash writing */
    FLASH_WaitForWriteEnd();
}

/**
  * @brief  Erases the entire FLASH.
  * @param  None
  * @retval None
  */
void FLASH_EraseBlock(uint32_t BlockAddr)
{
    /*!< Send write enable instruction */
    FLASH_WriteEnable();

    /*!< Bulk Erase */
    /*!< Select the FLASH: Chip Select low */
    FLASH_CS_LOW();
    /*!< Send Bulk Erase instruction  */
    FLASH_SendByte(FLASH_CMD_BE64);
     /*!< Send SectorAddr high nibble address byte */
    FLASH_SendByte((BlockAddr & 0xFF0000) >> 16);
    /*!< Send SectorAddr medium nibble address byte */
    FLASH_SendByte((BlockAddr & 0xFF00) >> 8);
    /*!< Send SectorAddr low nibble address byte */
    FLASH_SendByte(BlockAddr & 0xFF);
    /*!< Deselect the FLASH: Chip Select high */
    FLASH_CS_HIGH();

    /*!< Wait the end of Flash writing */
    FLASH_WaitForWriteEnd();
}

/**
  * @brief  Writes more than one byte to the FLASH with a single WRITE cycle 
  *         (Page WRITE sequence).
  * @note   The number of byte can't exceed the FLASH page size.
  * @param  pBuffer: pointer to the buffer  containing the data to be written
  *         to the FLASH.
  * @param  WriteAddr: FLASH's internal address to write to.
  * @param  NumByteToWrite: number of bytes to write to the FLASH, must be equal
  *         or less than "sFLASH_PAGESIZE" value.
  * @retval None
  */

void FLASH_WriteByte(uint8_t Byte, uint32_t WriteAddr)
{
    /*!< Enable the write access to the FLASH */
    FLASH_WriteEnable();

    /*!< Select the FLASH: Chip Select low */
    FLASH_CS_LOW();
    /*!< Send "Write to Memory " instruction */
    FLASH_SendByte(FLASH_CMD_PP);
    /*!< Send WriteAddr high nibble address byte to write to */
    FLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
    /*!< Send WriteAddr medium nibble address byte to write to */
    FLASH_SendByte((WriteAddr & 0xFF00) >> 8);
    /*!< Send WriteAddr low nibble address byte to write to */
    FLASH_SendByte(WriteAddr & 0xFF);
    /*!< Send a byte */
    FLASH_SendByte(Byte);

    /*!< Deselect the FLASH: Chip Select high */
    FLASH_CS_HIGH();

    /*!< Wait the end of Flash writing */
    FLASH_WaitForWriteEnd();
}


void FLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	
	/*!< Enable the write access to the FLASH */
    FLASH_WriteEnable();
	
	 /*!< Select the FLASH: Chip Select low */
    FLASH_CS_LOW();

    /*!< Send "Write to Memory " instruction */
    FLASH_SendByte(FLASH_CMD_PP);
    /*!< Send WriteAddr high nibble address byte to write to */
    FLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
    /*!< Send WriteAddr medium nibble address byte to write to */
    FLASH_SendByte((WriteAddr & 0xFF00) >> 8);
    /*!< Send WriteAddr low nibble address byte to write to */
    FLASH_SendByte(WriteAddr & 0xFF);

    /*!< while there is data to be written on the FLASH */
    while (NumByteToWrite--)
    {
        /*!< Send the current byte */
        FLASH_SendByte(*pBuffer);
        /*!< Point on the next byte to be written */
        pBuffer++;
    }
	
	/*!< Deselect the FLASH: Chip Select high */
    FLASH_CS_HIGH();

    /*!< Wait the end of Flash writing */
    FLASH_WaitForWriteEnd();
	
}

/**
  * @brief  Writes block of data to the FLASH. In this function, the number of
  *         WRITE cycles are reduced, using Page WRITE sequence.
  * @param  pBuffer: pointer to the buffer  containing the data to be written
  *         to the FLASH.
  * @param  WriteAddr: FLASH's internal address to write to.
  * @param  NumByteToWrite: number of bytes to write to the FLASH.
  * @retval None
  */
void FLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    Addr = WriteAddr % FLASH_SPI_PAGESIZE;
    count = FLASH_SPI_PAGESIZE - Addr;
    NumOfPage =  NumByteToWrite / FLASH_SPI_PAGESIZE;
    NumOfSingle = NumByteToWrite % FLASH_SPI_PAGESIZE;

    if (Addr == 0) /*!< WriteAddr is FLASH_PAGESIZE aligned  */
    {
        if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
        {
            FLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
        }else /*!< NumByteToWrite > sFLASH_PAGESIZE */
        {
            while (NumOfPage--)
            {
                FLASH_WritePage(pBuffer, WriteAddr, FLASH_SPI_PAGESIZE);
                WriteAddr +=  FLASH_SPI_PAGESIZE;
                pBuffer += FLASH_SPI_PAGESIZE;
            }

            FLASH_WritePage(pBuffer, WriteAddr, NumOfSingle);
        }
    }else /*!< WriteAddr is not sFLASH_PAGESIZE aligned  */
    {
        if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
        {
            if (NumOfSingle > count) /*!< (NumByteToWrite + WriteAddr) > sFLASH_PAGESIZE */
            {
                temp = NumOfSingle - count;

                FLASH_WritePage(pBuffer, WriteAddr, count);
                WriteAddr +=  count;
                pBuffer += count;

                FLASH_WritePage(pBuffer, WriteAddr, temp);
            }else
            {
                FLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
            }
        }else /*!< NumByteToWrite > sFLASH_PAGESIZE */
        {
            NumByteToWrite -= count;
            NumOfPage =  NumByteToWrite / FLASH_SPI_PAGESIZE;
            NumOfSingle = NumByteToWrite % FLASH_SPI_PAGESIZE;

            FLASH_WritePage(pBuffer, WriteAddr, count);
            WriteAddr +=  count;
            pBuffer += count;

            while (NumOfPage--)
            {
                FLASH_WritePage(pBuffer, WriteAddr, FLASH_SPI_PAGESIZE);
                WriteAddr +=  FLASH_SPI_PAGESIZE;
                pBuffer += FLASH_SPI_PAGESIZE;
            }

            if (NumOfSingle != 0)
            {
                FLASH_WritePage(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

/**
  * @brief  Reads a block of data from the FLASH.
  * @param  pBuffer: pointer to the buffer that receives the data read from the FLASH.
  * @param  ReadAddr: FLASH's internal address to read from.
  * @param  NumByteToRead: number of bytes to read from the FLASH.
  * @retval None
  */
void FLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    /*!< Select the FLASH: Chip Select low */
    FLASH_CS_LOW();

    /*!< Send "Read from Memory " instruction */
    FLASH_SendByte(FLASH_CMD_READ);

    /*!< Send ReadAddr high nibble address byte to read from */
    FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
    /*!< Send ReadAddr medium nibble address byte to read from */
    FLASH_SendByte((ReadAddr& 0xFF00) >> 8);
    /*!< Send ReadAddr low nibble address byte to read from */
    FLASH_SendByte(ReadAddr & 0xFF);

    while (NumByteToRead--) /*!< while there is data to be read */
    {
        /*!< Read a byte from the FLASH */
        *pBuffer = FLASH_SendByte(FLASH_DUMMY_BYTE);
        /*!< Point to the next location where the byte read will be saved */
        pBuffer++;
    }

    /*!< Deselect the FLASH: Chip Select high */
    FLASH_CS_HIGH();
}

uint8_t FLASH_ReadOneByte(uint32_t ReadAddr)
{
    static uint8_t Rev;
    /*!< Select the FLASH: Chip Select low */
    FLASH_CS_LOW();

    /*!< Send "Read from Memory " instruction */
    FLASH_SendByte(FLASH_CMD_READ);

    /*!< Send ReadAddr high nibble address byte to read from */
    FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
    /*!< Send ReadAddr medium nibble address byte to read from */
    FLASH_SendByte((ReadAddr& 0xFF00) >> 8);
    /*!< Send ReadAddr low nibble address byte to read from */
    FLASH_SendByte(ReadAddr & 0xFF);

    Rev =  FLASH_ReadByte();

    /*!< Deselect the FLASH: Chip Select high */
    FLASH_CS_HIGH();
    return Rev;
}

/**
  * @brief  Reads FLASH identification.
  * @param  None
  * @retval FLASH identification
  */
uint32_t FLASH_ReadID(void)
{
    uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

    /*!< Select the FLASH: Chip Select low */
    FLASH_CS_LOW();

    /*!< Send "RDID " instruction */
    FLASH_SendByte(0x9F);

    /*!< Read a byte from the FLASH */
    Temp0 = FLASH_SendByte(FLASH_DUMMY_BYTE);

    /*!< Read a byte from the FLASH */
    Temp1 = FLASH_SendByte(FLASH_DUMMY_BYTE);

    /*!< Read a byte from the FLASH */
    Temp2 = FLASH_SendByte(FLASH_DUMMY_BYTE);

    /*!< Deselect the FLASH: Chip Select high */
    FLASH_CS_HIGH();

    Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

    return Temp;
}

/**
  * @brief  Initiates a read data byte (READ) sequence from the Flash.
  *   This is done by driving the /CS line low to select the device, then the READ
  *   instruction is transmitted followed by 3 bytes address. This function exit
  *   and keep the /CS line low, so the Flash still being selected. With this
  *   technique the whole content of the Flash is read with a single READ instruction.
  * @param  ReadAddr: FLASH's internal address to read from.
  * @retval None
  */
void FLASH_StartReadSequence(uint32_t ReadAddr)
{
    /*!< Select the FLASH: Chip Select low */
    FLASH_CS_LOW();

    /*!< Send "Read from Memory " instruction */
    FLASH_SendByte(FLASH_CMD_READ);

    /*!< Send the 24-bit address of the address to read from -------------------*/
    /*!< Send ReadAddr high nibble address byte */
    FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
    /*!< Send ReadAddr medium nibble address byte */
    FLASH_SendByte((ReadAddr& 0xFF00) >> 8);
    /*!< Send ReadAddr low nibble address byte */
    FLASH_SendByte(ReadAddr & 0xFF);
}

/**
  * @brief  Reads a byte from the SPI Flash.
  * @note   This function must be used only if the Start_Read_Sequence function
  *         has been previously called.
  * @param  None
  * @retval Byte Read from the SPI Flash.
  */
uint8_t FLASH_ReadByte(void)
{
    return (FLASH_SendByte(FLASH_DUMMY_BYTE));
}

/**
  * @brief  Sends a byte through the SPI interface and return the byte received
  *         from the SPI bus.
  * @param  byte: byte to send.
  * @retval The value of the received byte.
  */
uint8_t FLASH_SendByte(uint8_t byte)
{
    /*!< Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPI1, byte);

    /*!< Wait to receive a byte */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

    /*!< Return the byte read from the SPI bus */
    return SPI_I2S_ReceiveData(SPI1);
}

/**
  * @brief  Sends a Half Word through the SPI interface and return the Half Word
  *         received from the SPI bus.
  * @param  HalfWord: Half Word to send.
  * @retval The value of the received Half Word.
  */
uint16_t FLASH_SendHalfWord(uint16_t HalfWord)
{
    /*!< Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

    /*!< Send Half Word through the sFLASH peripheral */
    SPI_I2S_SendData(SPI1, HalfWord);

    /*!< Wait to receive a Half Word */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

    /*!< Return the Half Word read from the SPI bus */
    return SPI_I2S_ReceiveData(SPI1);
}

/**
  * @brief  Disables the write access to the FLASH.
  * @param  None
  * @retval None
  */
void FLASH_WriteDisable(void)
{
    /*!< Select the FLASH: Chip Select low */
    FLASH_CS_LOW();

    /*!< Send "Write Enable" instruction */
    FLASH_SendByte(FLASH_CMD_WRDIS);

    /*!< Deselect the FLASH: Chip Select high */
    FLASH_CS_HIGH();
}


/**
  * @brief  Enables the write access to the FLASH.
  * @param  None
  * @retval None
  */
void FLASH_WriteEnable(void)
{
    /*!< Select the FLASH: Chip Select low */
    FLASH_CS_LOW();

    /*!< Send "Write Enable" instruction */
    FLASH_SendByte(FLASH_CMD_WREN);

    /*!< Deselect the FLASH: Chip Select high */
    FLASH_CS_HIGH();
}
/**
 * */
uint8_t FLASH_ReadStatusRegister(uint8_t SelectStatusRegister_1_2)
{
	uint8_t	status=0;
    /*!< Select the FLASH: Chip Select low */
    FLASH_CS_LOW();

	if(SelectStatusRegister_1_2 == 1)
	{
		FLASH_SendByte(FLASH_CMD_RESR1);
		status=FLASH_SendByte(FLASH_DUMMY_BYTE);	
	}
	else if(SelectStatusRegister_1_2 == 2)
	{
		FLASH_SendByte(FLASH_CMD_RESR2);
		status=FLASH_SendByte(FLASH_DUMMY_BYTE);	
	}	

    /*!< Deselect the FLASH: Chip Select high */
    FLASH_CS_HIGH();
	return status;
}

/**
  * @brief  Polls the status of the Write In Progress (WIP) flag in the FLASH's
  *         status register and loop until write opertaion has completed.
  * @param  None
  * @retval None
  */
void FLASH_WaitForWriteEnd(void)
{
    uint8_t flashstatus = 0;

    Delay_ms(1);
    /*!< Select the FLASH: Chip Select low */
    FLASH_CS_LOW();

    /*!< Send "Read Status Register" instruction */
    FLASH_SendByte(FLASH_CMD_RESR1);

    /*!< Loop as long as the memory is busy with a write cycle */
    do
    {
        /*!< Send a dummy byte to generate the clock needed by the FLASH
        and put the value of the status register in FLASH_Status variable */
        flashstatus = FLASH_SendByte(FLASH_DUMMY_BYTE);
        Delay_ms(1);

    }
    while ((flashstatus & 0x01) == 0x01); /* Write in progress */

    /*!< Deselect the FLASH: Chip Select high */
    FLASH_CS_HIGH();
}

void FLASH_LowLevel_DeInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*!< Disable the SPI1  */
    SPI_Cmd(SPI1, DISABLE);

    /*!< DeInitializes the SPI1 */
    SPI_I2S_DeInit(SPI1);

    /*!< SPI1 Periph clock disable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, DISABLE);

    /*!< Configure GPIO_SPI1_PIN_CLK : SCK */
    GPIO_InitStructure.GPIO_Pin = GPIO_SPI1_PIN_CLK;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIO_SPI1_PORT, &GPIO_InitStructure);

    /*!< Configure sFLASH_SPI pins: MISO */
    GPIO_InitStructure.GPIO_Pin = GPIO_SPI1_PIN_MISO;
    GPIO_Init(GPIO_SPI1_PORT, &GPIO_InitStructure);

    /*!< Configure sFLASH_SPI pins: MOSI */
    GPIO_InitStructure.GPIO_Pin = GPIO_SPI1_PIN_MOSI;
    GPIO_Init(GPIO_SPI1_PORT, &GPIO_InitStructure);

    /*!< Configure sFLASH_CS_PIN pin: sFLASH Card CS pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_SPI1_PIN_SS;
    GPIO_Init(GPIO_SPI1_PORT, &GPIO_InitStructure);
}

void FLASH_LowLevel_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
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
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
