/************************************************
 功能:STM32F103ZET6驱动GC9A01(touch)显示图像,触摸后切换箭头
 
 接线说明
	GC9A01(touch)	stm32F10x
	
	3V3				VIN
	GND				GND
	BL				PB7
	RST				PA6
	CS				PB6
	RS				PA7
	WR				PA5
	RD				PA4
	DB0				PC3
	DB1				PC4
	DB2				PC5
	DB3				PC6
	DB4				PC7
	DB5				PC8
	DB6				PC9
	DB7				PC10
	T_RST			---
	T_INT			PB5
	T_SCL			PB0		
	T_SDA			PB1
	
 
 作者：JXL
************************************************/

#include "pbdata.h"
#include "lcd_init.h"
#include "lcd.h"
#include "image.h"
#include "CST816.h"

uint8_t touch_state=0,while_one=1;

int main(void)
{
	LCD_Init();

	if(!init_CST816())
	{
		delay_ms(500);
	}
		
	LCD_Fill(0,0,LCD_W,LCD_H,0xFFF0);   //填充为白色背景色
	LCD_ShowPicture(0,0,LCD_W,LCD_H,YXDZ_logo);   //显示一张图片
	while(1)
	{
		CST816_available();
		if((CST816_event() == 2))
		{
			if((CST816_Gesture() == LONG_PRESS || CST816_Gesture() == SWIPE_DOWN || CST816_Gesture() == SWIPE_UP || CST816_Gesture() == SWIPE_RIGHT || CST816_Gesture() == SWIPE_LEFT) && CST816_Gesture() != touch_state)
			{
				if(while_one)
				{
					while_one = 0;
					LCD_Fill(0,0,240,240,WHITE);
				}
				switch (touch_state)
				{
					case SWIPE_DOWN: 
								LCD_Fill(85,70,155,170,WHITE);
								break;
					case SWIPE_UP: 
								LCD_Fill(85,70,155,170,WHITE);
								break;
					case SWIPE_RIGHT: 
								LCD_Fill(70,85,170,155,WHITE);
								break;
					case SWIPE_LEFT:
								LCD_Fill(70,85,170,155,WHITE);
								break;
					case LONG_PRESS:
								LCD_Fill(0,0,240,240,WHITE);
								break;
					default:
						break;
				}
				
				switch (CST816_Gesture())
				{
					case SWIPE_DOWN: 
								touch_state = CST816_Gesture();
								LCD_ShowPicture(85,70,70,100,Down_Direction);
								break;
					case SWIPE_UP: 
								touch_state = CST816_Gesture();
								LCD_ShowPicture(85,70,70,100,UP_Direction);
								break;
					case SWIPE_RIGHT: 
								touch_state = CST816_Gesture();
								LCD_ShowPicture(70,85,100,70,R_Direction);
								break;
					case SWIPE_LEFT:
								touch_state = CST816_Gesture();
								LCD_ShowPicture(70,85,100,70,L_Direction);
								break;
					case LONG_PRESS:
								touch_state = CST816_Gesture();
								LCD_ShowPicture(0,0,LCD_W,LCD_H,YXDZ_logo);
								break;
					default:
						break;
				}
			}
		}
	}
}

