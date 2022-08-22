/************************************************
 功能:STM32F407驱动GC9A01显示图像
 
 接线说明
	GC9A01			stm32F407
	
	3V3				VIN
	GND				GND
	SCL				PB9
	SDA				PB8
	RES				PB6
	DC				PB7
	CS				PB4
	BLK				PB5
 
 作者：JXL
************************************************/

#include "stm32f4xx.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_init.h"
#include "image.h"


int main(void)
{
	delay_init(168);
	LCD_Init();
	LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
  while(1)
	{
		LCD_ShowPicture(0,0,LCD_W,LCD_H,YXDZ_logo);
	}
}


