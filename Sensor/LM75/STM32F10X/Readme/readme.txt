接线说明

	LM75使用端口定义在 softIIC.h 文件中,代码未封装成库，因此LM75部分初始化代码在main.c中,用户可以自行移植优化
	
	串口参数：96N81

	默认接线如下
	LM75          STM32F10X
	VCC           3V3
	GND           GND
	SCL           PB6
	SDA           PB7
	
代码说明

	stm32f10x启动后检测是否接入LM75，若没有接入则定时500ms一次返回 未检测到传感器 的提示
	
	成功检测到LM75后，代码将会配置config寄存器的参数，具体参数可以参考LM75.h或手册,配置参数设置完成后继续设置上下限报警温度
	
	设置完以上参数后，循环部分定时500ms一次返回温度数据







