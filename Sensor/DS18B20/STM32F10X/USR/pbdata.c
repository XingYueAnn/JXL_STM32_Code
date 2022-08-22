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


/* 配置GPIO为为输入模式*/
void Gpio_Config_FLOATING_In()
{
    /*对GPIO初始化*/
 	GPIO_InitTypeDef   GPIO_Init_Structure;

	GPIO_Init_Structure.GPIO_Pin=GPIO_Pin_0;

	GPIO_Init_Structure.GPIO_Speed=GPIO_Speed_50MHz;

	/*设置IO口为浮空输入模式*/ 
 	GPIO_Init_Structure.GPIO_Mode= GPIO_Mode_IN_FLOATING;

	GPIO_Init( GPIOA,  &GPIO_Init_Structure);
}

/* 配置GPIO为为输出模式*/
void Gpio_Config_Mode_Out()
{
    /*对GPIO初始化*/
 	GPIO_InitTypeDef   GPIO_Init_Structure;

	GPIO_Init_Structure.GPIO_Pin=GPIO_Pin_0;

	GPIO_Init_Structure.GPIO_Speed=GPIO_Speed_50MHz;

	/*设置IO口为开漏输出模式*/ 
 	GPIO_Init_Structure.GPIO_Mode= GPIO_Mode_Out_OD;

	GPIO_Init( GPIOA,  &GPIO_Init_Structure);
}


int init18B20(void)
{
	int temp;
	DS18B20_DQ_OUT_High;
	delay_us(10);
	DS18B20_DQ_OUT_Low;
	delay_us(700);
	DS18B20_DQ_OUT_High;
	delay_us(45);
	temp=DS18B20_DQ_IN;
	delay_us(120);
	return (temp);
}



unsigned char read18B20()
{
	unsigned char temp1,n;
	for(n=0;n<8;n++)
	{
		DS18B20_DQ_OUT_High;
		delay_us(10);
		DS18B20_DQ_OUT_Low;
		delay_us(1);
		DS18B20_DQ_OUT_High;
		delay_us(10);
		temp1>>=1;
		if(DS18B20_DQ_IN==1)
		{
			temp1|=0x80;
		}
		else
		{
			temp1|=0x00;
		}
		delay_us(10);
	}
	return(temp1);
}


void write18B20(unsigned char temp2)
{
	unsigned char n;
	for(n=0;n<8;n++)
	{
		DS18B20_DQ_OUT_High;
		delay_us(1);
		DS18B20_DQ_OUT_Low;
		if(temp2&0x01)
		{
			DS18B20_DQ_OUT_High;
		}
		else
		{
			DS18B20_DQ_OUT_Low;
		}
		
		delay_us(60);
		DS18B20_DQ_OUT_High;
		delay_us(1);
		temp2>>=1;
	}
	delay_us(10);
}



void readwen()
{
	init18B20();
	write18B20(0xcc);
	write18B20(0x44);
	delay_ms(200);
	init18B20();
	write18B20(0xcc);
	write18B20(0xbe);
}

