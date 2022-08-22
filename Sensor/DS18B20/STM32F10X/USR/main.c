/************************************************
 功能:STM32F103ZET6驱动DS18B20采集温度串口1输出
 
 接线说明
	DS18B20       STM32F10X
	VCC           3V3
	GND           GND
	D0            PA0
	
	串口参数：96N81
 
	代码未封装,仅供测试使用,可自行移植
 
 作者：JXL
************************************************/

#include "pbdata.h"

void RCC_Configuration(void)//时钟初始化
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1串口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
}

void GPIO_Configuration(void)//GPIO端口配置
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*PA9,tx*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	/*PA10,rx*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	/*PA0，DS18B20使用端口*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
 	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;   //设置IO口为开漏输出模式*/ 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init( GPIOA,  &GPIO_InitStructure);
	
	//GPIO_InitTypeDef GPIO_InitStructure;
//	/*PA2,tx*/
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	/*PA3,rx*/
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//	/*led*/
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void NVIC_Configuration(void)//NVIC寄存器配置
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//设置分组
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;//使能USART1中断
	
	//NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;//使能USART2中断
	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//设置响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//使设置的IRQChannel通道使能
	NVIC_Init(&NVIC_InitStructure);//初始化到指定参数
}

void USRAT_Configuration(void)//USART配置
{
	USART_InitTypeDef USART_InitStructure;//声明USART的结构体变量
	USART_InitStructure.USART_BaudRate=9600;//设置波特率
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//设置数据位为8位传输
	USART_InitStructure.USART_StopBits=USART_StopBits_1;//设置停止位数目为1
	USART_InitStructure.USART_Parity=USART_Parity_No;//设置无奇偶效验位，96N8是没有校验位的
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//没有硬件流控制，设置硬件流控制失能
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//发送失能和接收失能
	USART_Init(USART1,&USART_InitStructure);//初始化为上述的指定参数
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//使能或失能指定的USART中断，这里使能USART的接收中断
	USART_Cmd(USART1,ENABLE);//使能或失能指定的USART外设
	
	USART_ClearFlag(USART1,USART_FLAG_TC/*发送完成标志位*/);//清除USARTx的待处理标志位
}

int fputc(int ch,FILE *f)//重写“stdio.h中的函数”
{
	USART_SendData(USART1,(u8)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//判断数据是否发送完成
	return ch;
}

//重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}

int main(void)
{
	
	unsigned char TL;
	unsigned char TH;
	
	unsigned char zhengshu;
	unsigned char xiaoshu;
	
	RCC_Configuration();
	GPIO_Configuration();
	USRAT_Configuration();
	NVIC_Configuration();
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	
	if(init18B20())
	{
		printf("未检测到DS18B20!");
	}
	else
	{
		printf("OK!");
	}
	
	while(1)
	{
		readwen();
		TL=read18B20();
		TH=read18B20();

		zhengshu=TH*16+TL/16;
		xiaoshu=(TL%16)*10/16;
		printf("温度：%d.%d\r\n",zhengshu,xiaoshu);
		
		delay_ms(1000);
	}
}


