#ifndef _W25QXX_H
#define _W25QXX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "define.h"
#include "stm32f10x_gpio.h"

/**
  * @brief  W25Q32 SPI Flash supported commands
  */  
#define FLASH_CMD_WREN           0x06  /* Write Enable */
#define FLASH_CMD_WRDIS          0x04  /* Write Disable */
#define FLASH_CMD_RESR1          0x05  /* Read Status Register-1 */
#define FLASH_CMD_RESR2          0x35  /* Read Status Register-2 */
#define FLASH_CMD_READ           0x03  /* Read data */
#define FLASH_CMD_WRSR           0x01  /* Write Status Register */
#define FLASH_CMD_PP             0x02  /* Page Program */
#define FLASH_CMD_QPP            0x32  /* Quad Page Program */
#define FLASH_CMD_BE64           0xD8  /* Block Erase (64KB) */
#define FLASH_CMD_BE32           0x52  /* Block Erase (32KB) */
#define FLASH_CMD_SE             0x20  /* Sector Erase (4KB) */
#define FLASH_CMD_CHIP_ERASE     0xC7  /* Chip Erase */
#define FLASH_CMD_ERASE_SUSPEN   0x75  /* Erase Suspend */
#define FLASH_CMD_ERASE_RESUME   0x7A  /* Erase Resume */
#define FLASH_CMD_POWER_DOW      0xB9  /* Power-down */
#define FLASH_CMD_HPM            0xA3  /* High Performance Mode */
#define FLASH_CMD_MBR            0xFF  /* Mode Bit Reset */
#define FLASH_CMD_EPD            0xAB  /* Release Power down */
#define FLASH_CMD_ID             0x90  /* Device ID */
#define FLASH_CMD_EUID           0x4B  /* Read Unique ID */

#define FLASH_DUMMY_BYTE 0xA5
#define FLASH_SPI_PAGESIZE 0x100
#define FLASH_ID 0xEF4016
#define FLASH_WriterAddress 20480
#define FLASH_ReadAddress 20480
#define FLASH_SectorToErase 20480
#define FLASH_Sizeof_TxBuffer sizeof(Tx_Buffer)


  
/**
  * @brief  Select FLASH: Chip Select pin low
  */
#define FLASH_CS_LOW()       GPIO_ResetBits(GPIO_SPI1_PORT, GPIO_SPI1_PIN_SS)
/**
  * @brief  Deselect FLASH: Chip Select pin high
  */
#define FLASH_CS_HIGH()      GPIO_SetBits(GPIO_SPI1_PORT, GPIO_SPI1_PIN_SS)   
/**
  * @}
  */ 
  


/** @defgroup Exported_Functions
  * @{
  */
/**
  * @brief  High layer functions
  */
void FLASH_DeInit(void);
void FLASH_Init(void);
void FLASH_EraseSector(uint32_t SectorAddr);
void FLASH_EraseBlock(uint32_t BlockAddr);
void FLASH_WriteByte(uint8_t Byte, uint32_t WriteAddr);
void FLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void FLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void FLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint8_t FLASH_ReadOneByte(uint32_t ReadAddr);
uint32_t FLASH_ReadID(void);
void FLASH_StartReadSequence(uint32_t ReadAddr);

/**
  * @brief  Low layer functions
  */
uint8_t FLASH_ReadByte(void);
uint8_t FLASH_SendByte(uint8_t byte);
uint16_t FLASH_SendHalfWord(uint16_t HalfWord);
void FLASH_WriteEnable(void);
void FLASH_WriteEnable(void);
uint8_t FLASH_ReadStatusRegister(uint8_t SelectStatusRegister_1_2);
void FLASH_WaitForWriteEnd(void);
void FLASH_LowLevel_DeInit(void);
void FLASH_LowLevel_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* _W25QXX_H */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
