#ifndef _LM75_H_
#define _LM75_H_

#define IIC_address  0x49  //7位IIC器件地址

/*配置寄存器部分参数,寄存器地址0x01,可根据手册自行增加*/
#define Low_alert  0x00   //OS警报端口输出低电平有效
#define High_alert  0x04   //OS警报端口输出高电平有效

#define Turn_off  0x01   //LM75进入关断模式

#define Comparator_output  0x00   //比较器输出
#define Interrupt_output  0x02   //中断输出



/*初始化，上电判断LM75是否响应来确定LM75是否接入
LM75接入返回0，未检测到返回1*/
int LM75_init_LM75(void);

/*读取16位温度数据并返回温度值
按照LM75手册说明获取到的数据需要乘0.125，该函数并未对此进行处理*/
int LM75_read_temperature(void);

/*写配置寄存器*/
void LM75_write_Configuration(unsigned char Configuration_register);

/*写低温报警寄存器，输入温度参数*/
void LM75_write_Low_temperature_alarm(int Low_temperature_alarm);

/*写高温报警寄存器，输入温度参数*/
void LM75_write_High_temperature_alarm(int High_temperature_alarm);

#endif

