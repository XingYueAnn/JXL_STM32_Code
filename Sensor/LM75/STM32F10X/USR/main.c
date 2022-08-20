#include "pbdata.h"

void RCC_Configuration(void)//时钟初始化
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(Pin_RCC,ENABLE);
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
	/*PB6,PB7，LM75使用端口*/
	GPIO_InitStructure.GPIO_Pin=SCL_Pin|SDA_Pin;
 	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;   //设置IO口为开漏输出模式*/ 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init( Pin_group,  &GPIO_InitStructure);
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
	RCC_Configuration();
	GPIO_Configuration();
	USRAT_Configuration();
	NVIC_Configuration();

	while(LM75_init_LM75())
	{
		printf("%s","初始化失败，未检测到LM75\r\n");
		delay_ms(500);
	}
	printf("%s","初始化成功，检测到LM75\r\n");
	LM75_write_Configuration(Low_alert|Comparator_output);
	LM75_write_Low_temperature_alarm(33);
	LM75_write_High_temperature_alarm(35);
	delay_ms(500);
	
	while(1)
	{
		float temperature;
    temperature=LM75_read_temperature()*0.125;
    printf("当前温度：%.2f\r\n",temperature);
		delay_ms(500);
	}
}


