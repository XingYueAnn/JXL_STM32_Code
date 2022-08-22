#ifndef _pbdata_H
#define _pbdata_H



#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_it.h"
#include "misc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "stdio.h"
#include "LM75.h"
#include "softIIC.h"


#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int
	
void delay(u16 nCount);
void delay_ms(u16 nCount);
void delay_us(u32 nCount);//us级延时


//定义变量

extern u8 dt;

#endif
