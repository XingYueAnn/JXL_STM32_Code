#include "pbdata.h"

u8 dt=0;

void delay(u16 nCount)
{
	while(nCount--)
	{
		u32 temp;
		SysTick->LOAD=9000;
		SysTick->VAL=0x00;
		SysTick->CTRL=0x01;
		do
		{
			temp=SysTick->CTRL;
		}while((temp&&0x01)&&(!(temp&(1<<16))));
		SysTick->CTRL=0x00;
		SysTick->VAL=0x00;
	}
}

void delay_ms(u16 nCount)
{
		u32 temp;
		SysTick->LOAD=9000*nCount;
		SysTick->VAL=0x00;
		SysTick->CTRL=0x01;
		do
		{
			temp=SysTick->CTRL;
		}while((temp&&0x01)&&(!(temp&(1<<16))));
		SysTick->CTRL=0x00;
		SysTick->VAL=0x00;
}

void delay_us(u32 nCount)//us级延时
{
	nCount=2*nCount;
	while(nCount--)
	{
	u32 temp;
	SysTick->LOAD=9;//重载初值计算为1ms的时间
	SysTick->VAL=0x00;//清空当前值寄存器，清空计数器
	SysTick->CTRL=0x01;//使能，减到0时无动作，采用外部时钟源
	do
	{
		temp=SysTick->CTRL;//读取当前倒计时所到的数值
	}while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达，即等待标志位变0
	SysTick->CTRL=0x00;//关闭计数器
	SysTick->VAL=0x00;//清空计数器
	}
}



