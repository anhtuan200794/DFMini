//lcd.c   
#include <stdio.h>   
//#include "stm32f2xx_usart.h"   
#include "stm32f10x_gpio.h"
#include "define.h"
   
#define  DAT   1    //����   
#define  COM   0    //����   

void delay(unsigned int MS);                    //�ڲ���ʱ   
void lcd_show_num(unsigned char data[]);   
void lcd_clr(void);
void write_Speed(float speed);

   
   
//һ��HT1621 4COM�ĳ��ñ���,��λ��COM0,��4bit��SEG0,��4bit��SEG1   
        //�ڰ���ʾλ      
//  _   
// |_|   ��Ե�8����ʾλ 1--f 2--e 3--d 4--c 5--g 6--b 7--a    
// |_|     
//     
//         
//unsigned char NUM[]={   
//  0x60,0x60,0x60,0xe0,0x60,0xe0,0x60,     // 0x60 -- 1   
//  0x3e,0xbe,0xbe,0x3e,0xbe,0xbe,0xbe,     // 0x3e -- 2   
//  0x7a,0x7a,0xfa,0xfa,0xfa,0xfa,0xfa,     // 0x7a -- 3   
//  0xe3,0x63,0x63,0xe3,0xe3,0xe3,0x63,     // 0x63 -- 4   
//  0xdb,0x5b,0xdb,0xdb,0xdb,0x5b,0xdb,     // 0x5b -- 5   
//  0xdf,0xdf,0xdf,0xdf,0xdf,0x5f,0xdf,     // 0x5f -- 6   
//  0x70,0x70,0x70,0xf0,0x70,0xf0,0xf0,     // 0x70 -- 7   
//  0xff,0xff,0xff,0xff,0xff,0xff,0xff,     // 0x7f -- 8   
//  0xfb,0x7b,0xfb,0xfb,0xfb,0xfb,0xfb,     // 0x7b -- 9   
//  0xfd,0xfd,0xfd,0xfd,0x7d,0xfd,0xfd,     // 0x7d -- 0   
//};   
unsigned char NumCode1[10] = { 0xd7,0x06,0xe3,0xa7,0x36,0xb5,0xf5,0x07,0xf7,0xb7 };
unsigned char NumCode2[10] = { 0x7d,0x60,0x3e,0x7a,0x63,0x5b,0x5f,0x70,0x7f,0x7b };

   
void write_mode(unsigned char MODE) //д��ģʽ,����or����   
{   
    GPIO_ResetBits(LCD_PORT,HT1621_WR);                                //  RW = 0;   
    delay(10);   
    GPIO_SetBits(LCD_PORT,HT1621_DAT);                                 //  DA = 1;   
    GPIO_SetBits(LCD_PORT,HT1621_WR);                                  //  RW = 1;   
    delay(10);   
       
    GPIO_ResetBits(LCD_PORT,HT1621_WR);                                //  RW = 0;   
    delay(10);   
    GPIO_ResetBits(LCD_PORT,HT1621_DAT);                               //  DA = 0;   
    GPIO_SetBits(LCD_PORT,HT1621_WR);                                  //  RW = 1;   
    delay(10);   
       
    GPIO_ResetBits(LCD_PORT,HT1621_WR);                                //  RW = 0;   
    delay(10);   
   
    if(0==MODE)   
    {   
        GPIO_ResetBits(LCD_PORT,HT1621_DAT);                           //  DA = 0;   
    }   
    else   
    {   
        GPIO_SetBits(LCD_PORT,HT1621_DAT);                             //  DA = 1;   
    }   
    delay(10);   
    GPIO_SetBits(LCD_PORT,HT1621_WR);                                  //  RW = 1;   
    delay(10);   
}   

   
void write_command(unsigned char Cbyte)                             //д�������9bit,���1bitû��   
{   
    unsigned char i;   
    for(i=0;i<8;i++)   
    {   
        GPIO_ResetBits(LCD_PORT,HT1621_WR);                            //  RW = 0;   
        delay(10);   
   
        if((Cbyte>>(7-i)) & 0x01)   
        {   
            GPIO_SetBits(LCD_PORT,HT1621_DAT);                         //  DA = 1;   
        }   
        else   
        {   
            GPIO_ResetBits(LCD_PORT,HT1621_DAT);                       //  DA = 0;   
        }   
        delay(10);   
        GPIO_SetBits(LCD_PORT,HT1621_WR);                              //  RW = 1;   
        delay(10);   
    }   
    GPIO_ResetBits(LCD_PORT,HT1621_WR);                                //  RW = 0;   
    delay(10);   
    GPIO_ResetBits(LCD_PORT,HT1621_DAT);                               //  DA = 0; ��9bit,������,���Ǳ���д��   
    GPIO_SetBits(LCD_PORT,HT1621_WR);                                  //  RW = 1;   
    delay(10);   
}   
    

void write_data(unsigned char data, unsigned char cnt)
{
    unsigned char i;
    for (i = 0; i < cnt; i++)
    {
        GPIO_ResetBits(LCD_PORT,HT1621_WR);                            //  RW = 0;   
        delay(10);   
        if (data & 0x80)
        {
            GPIO_SetBits(LCD_PORT, HT1621_DAT);
        }
        else
        {
            GPIO_ResetBits(LCD_PORT, HT1621_DAT);
        } 
        GPIO_SetBits(LCD_PORT,HT1621_WR);                              //  RW = 1;   
        delay(10); 
        data <<= 1;
    }
}
void wrone(unsigned char addr, unsigned char sdata)
{
    addr <<= 2;
    GPIO_ResetBits(LCD_PORT, HT1621_CS);
    write_data(0xa0, 3);
    write_data(addr, 6);
    write_data(sdata, 8);
    GPIO_SetBits(LCD_PORT, HT1621_CS);
}

void delay(unsigned int MS)                                         //��ʱ   
{   
    unsigned char us,usn;   
    while(MS!=0)   
    {    
        usn = 2;   
        while(usn!=0)   
        {   
            us=0xf2;   
            while (us!=0){us--;};   
            usn--;   
        }   
        MS--;   
    }   
}   
   

void lcd_init( void )                                               //��ʼ��   
{   
    GPIO_ResetBits(LCD_PORT,HT1621_CS);                                //CS = 0;   
    write_mode(COM);        //����ģʽ   
    write_command(0x01);    //Enable System   
    write_command(0x03);    //Enable Bias   
    write_command(0x04);    //Disable Timer   
    write_command(0x05);    //Disable WDT   
    write_command(0x08);    //Tone OFF   
    write_command(0x18);    //on-chip RC��   
    write_command(0x29);    //1/4Duty 1/3Bias   
    write_command(0x80);    //Disable IRQ   
    write_command(0x40);    //Tone Frequency 4kHZ   
    write_command(0xE3);    //Normal Mode   
    GPIO_SetBits(LCD_PORT,HT1621_CS);                                  //CS = 1;   
}   
  
void wrCLR(void)
{
    unsigned char addr = 0;
    unsigned char i;
    for (i = 0; i < 30; i++)
    {
        write_data(addr, 0x00);
        addr = addr + 2;
    }
}
   
void lcd_show_num(unsigned char data[])   
{   
    char i = 0 ;   
    unsigned char show_buf[4];   
       
    for(i=0;i<4;i++)                                             //ȡǰ��λ��ʾ��   
    {   
        switch(data[i])   
        {   
            case '0':   
                    show_buf[i] = 0x7d;   
                    break;   
            case '1':   
                    show_buf[i] = 0x60;   
                    break;   
            case '2':   
                    show_buf[i] = 0x3e;   
                    break;   
            case '3':   
                    show_buf[i] = 0x7a;   
                    break;   
            case '4':   
                    show_buf[i] = 0x63;   
                    break;   
            case '5':   
                    show_buf[i] = 0x5b;   
                    break;   
            case '6':   
                    show_buf[i] = 0x5f;   
                    break;   
            case '7':   
                    show_buf[i] = 0x70;   
                    break;   
            case '8':   
                    show_buf[i] = 0x7f;   
                    break;   
            case '9':   
                    show_buf[i] = 0x7b;   
                    break;   
        }   
    }  
    wrone(6, show_buf[0]);
    wrone(4, show_buf[1]);
    wrone(2, show_buf[2]);
}  

void write_Speed(float speed)
{
    wrone(6, 0x00);         //clear LCD
    wrone(4, 0x00);
    wrone(2, 0x00);
    int iSpeed = (int)(speed*10);
    int iTemp;
    iTemp = iSpeed%100;
    //char sSpeed[3];
    //sprintf(sSpeed,"%ld", iSpeed);
    if((iSpeed/100) == 0)
    {
        wrone(6, (0x00 | 0x80));
    } else
    {
        wrone(6, (NumCode2[iSpeed/100] | 0x80));
    }
    wrone(4, (NumCode2[iTemp/10] | 0x80));
    wrone(2, NumCode2[iTemp%10]);
}

void lcd_test(void)   
{   
    delay(20);   
    lcd_init();   
    //lcd_clr();
    wrCLR();
    while(1)   
    {      
        write_Speed(2.4);
        delay(50000);
        wrCLR();
        write_Speed(12.4);
        delay(50000);
        wrCLR();
        write_Speed(10.4);
        delay(50000);
        wrCLR();
        write_Speed(0.8);
        delay(50000);
    }

}   

/***************************************************end file*************************************************/   