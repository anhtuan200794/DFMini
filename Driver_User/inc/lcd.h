//lcd.h 
 
#ifndef	_LCD_H_ 
#define _LCD_H_ 

void lcd_init(void);						// lcd ģ���ʼ��	 
void lcd_show_num(unsigned char data[]);		// lcd ��ʾ��������ϣ����ʾ��12345678�����ɴ��롰12345678����data�ĳ̶Ȳ���С��8 
void lcd_clr(void);							// lcd �������� 
void lcd_test(void);						// lcd ���Ժ��� 
 
#endif