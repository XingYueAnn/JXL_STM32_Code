#include "pbdata.h"

#define DS18B20_DQ_OUT_Low GPIO_ResetBits(GPIOA,GPIO_Pin_0)  //数据端口	PA0 
#define DS18B20_DQ_OUT_High GPIO_SetBits(GPIOA,GPIO_Pin_0)  //数据端口	PA0 
#define DS18B20_DQ_IN GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)   //数据端口	PA0
#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int
void Init_Ds18b20(void);
void Write_one_byte(u8 a);
u8 Read_one_byte(void);
u8 wen_du_huo_qu(void);
void Gpio_Config(void);
void Gpio_Config_Mode_In(void);
void Gpio_Config_Mode_Out(void);
void SysTick_Init(void);
//void Delay_us(__IO u32 nTime);
