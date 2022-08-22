/************************************************
 功能:STM32F103ZET6驱动GC9A01显示图像
 
 接线说明
	GC9A01		stm32F10x
	
	3V3				VIN
	GND				GND
	SCL				PA5
	SDA				PA4
	RES				PA6
	DC				PA7
	CS				PB6
	BLK				PB7
 
 作者：JXL
************************************************/

#include "pbdata.h"
#include "lcd_init.h"
#include "lcd.h"

#include "image.h"

int main(void)
{
	LCD_Init();
	LCD_Fill(0,0,LCD_W,LCD_H,WHITE);   //填充为白色背景色
	while(1)
	{
		LCD_ShowPicture(0,0,LCD_W,LCD_H,YXDZ_logo);   //显示一张图片
	}
}

