#include "softi2c.h"
#include "stm32f10x_gpio.h"
#include "define.h"
#include "delay.h"

static void SOFT_I2c_Ack(void);
static void SOFT_I2c_Nack(void);
static void SOFT_I2c_Clk(void);
static void SOFT_I2c_Out(void);
static void SOFT_I2c_In(void);

/***************************************************************************************************
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none
 * description  :This function is used to initialize the I2C module.
***************************************************************************************************/
void SOFT_I2c_Init(void)
{
    SDA_HIGH();
    SCL_HIGH();
}

/***************************************************************************************************
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none
 * description  :This function is used to generate I2C Start Condition.
                 Start Condition: SDA goes low when SCL is High.
***************************************************************************************************/
void SOFT_I2c_Start(void)
{
    SDA_HIGH();
    SCL_HIGH();
    Delay_us(5);
    SDA_LOW();
    Delay_us(5);
    SCL_LOW();
}
/***************************************************************************************************
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none
 * description  :This function is used to generate I2C Stop Condition.
                 Stop Condition: SDA goes High when SCL is High.
***************************************************************************************************/
void SOFT_I2c_Stop(void)
{
    SDA_LOW();
    SCL_LOW();
    Delay_us(5);
    SCL_HIGH();
    Delay_us(5);
    SDA_HIGH();
}
/***************************************************************************************************
****************************************************************************************************
 * I/P Arguments: uint8_t-->8bit data to be sent.
 * Return value  : none
 * description  :This function is used to send a byte on SDA line using I2C protocol
                 8bit data is sent bit-by-bit on each clock cycle.
                 MSB(bit) is sent first and LSB(bit) is sent at last.
                 Data is sent when SCL is low.
***************************************************************************************************/
void SOFT_I2c_Write(uint8_t data)
{
    for(uint8_t i = 0; i < 8; i++)
    {

        if((data & 0x80) == 0x80)
        {
            SDA_HIGH();
        }else
        {
        
            SDA_LOW();
        }
        data <<= 1;
        SOFT_I2c_Clk();
    }
    SOFT_I2c_Clk();
}

void SOFT_I2c_Write_Byte(uint8_t data)
{
    SOFT_I2c_Start();
    SOFT_I2c_Write(ADDRESS_SLAVE<<1);
    SOFT_I2c_Write(data);
    SOFT_I2c_Stop();
}
/***************************************************************************************************
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : uint8_t(received byte)
 * description :This fun is used to receive a byte on SDA line using I2C protocol.
               8bit data is received bit-by-bit each clock and finally packed into Byte.
               MSB(bit) is received first and LSB(bit) is received at last.
***************************************************************************************************/
uint8_t SOFT_I2c_Read(uint8_t reg)
{
    return 0;
}
/***************************************************************************************************
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none
 * description  :This function is used to generate a the Positive ACK
                 pulse on SDA after receiving a byte.
***************************************************************************************************/
static void SOFT_I2c_Ack(void)
{

}
/***************************************************************************************************
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none
 * description  :This function is used to generate a the Negative/NO ACK
                 pulse on SDA after receiving all bytes.
***************************************************************************************************/
static void SOFT_I2c_Nack(void)
{

}
/***************************************************************************************************
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none
 * description  :This function is used to generate a clock pulse on SCL line.
***************************************************************************************************/
static void SOFT_I2c_Clk(void)
{
    Delay_us(5);
    SCL_HIGH();
    Delay_us(5);
    SCL_LOW();
    
}
/***************************************************************************************************
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none
 * description  
***************************************************************************************************/
static void SOFT_I2c_Out(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_SCL_PIN|GPIO_SDA_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_I2C_PORT, &GPIO_InitStructure);
}
/***************************************************************************************************
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none
 * description  
***************************************************************************************************/
static void SOFT_I2c_In(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_SCL_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_I2C_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIO_I2C_PORT, &GPIO_InitStructure);
}