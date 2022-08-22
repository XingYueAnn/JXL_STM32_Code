#ifndef _stm32f10x_oled_H
#define _stm32f10x_oled_H

#include "pbdata.h"



void RCC_Configuration(void);//初始化写OLED要使用端口的时钟

void IIC_Start(void);//IIC起始段函数

void IIC_Stop(void);//IIC停止段函数

void IIC_Wait_Ack(void);//等待确认

void Write_IIC_Byte(unsigned char IIC_Byte);//按位写入一个字节

void Write_IIC_Command(unsigned char IIC_Command);//写指令

void Write_IIC_Data(unsigned char IIC_Data);//写数据

void OLED_WR_Byte(unsigned dat,unsigned cmd);//指定写入的是指令还是数据

void fill_picture(unsigned char fill_Data);//填入图片

void OLED_Set_Pos(unsigned char x, unsigned char y);//坐标设置

void OLED_Display_On(void);//开启OLED显示

void OLED_Display_Off(void);//关闭OLED显示

void OLED_Clear(void);//清屏函数

void OLED_On(void);

/*
		在指定位置显示一个字符,包括部分字符
		x:0~127
		y:0~63
		mode:0,反白显示;1,正常显示				 
		size:选择字体 16/12 
*/
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);

u32 oled_pow(u8 m,u8 n);//m^n函数

/*
		显示2个数字
		x,y :起点坐标	 
		len :数字的位数
		size:字体大小
		mode:模式	0,填充模式;1,叠加模式
		num:数值(0~4294967295)
*/
void OLED_ShowNum(u8 x,u8 y,signed int num,u8 len,u8 size2);

void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size);//显示一个字符串

void OLED_ShowCHinese(u8 x,u8 y,u8 no);//显示汉字

/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);

void OLED_Init(void);//初始化ssd1306


#endif
