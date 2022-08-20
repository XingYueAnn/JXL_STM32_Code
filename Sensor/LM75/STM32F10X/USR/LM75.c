#include "pbdata.h"


int LM75_init_LM75(void)
{
	int state=0;
	soft_begin();
	soft_IIC_Start();
	state=soft_write_address(0,IIC_address);
	soft_write_Byte(0x00);
	soft_IIC_Start();
	soft_write_address(1,IIC_address);
	soft_read_Byte(0);
	soft_read_Byte(1);
	soft_IIC_Stop();
	return (state);
}

int LM75_read_temperature(void)
{
	int temperature_TH,temperature_TL,temperature;
	soft_IIC_Start();
	soft_write_address(0,IIC_address);
	soft_write_Byte(0x00);
	soft_IIC_Start();
	soft_write_address(1,IIC_address);
	
	temperature_TH=soft_read_Byte(0);
	temperature_TL=soft_read_Byte(1);
	soft_IIC_Stop();
	temperature=(temperature_TH<<3)|(temperature_TL>>5);
	return(temperature);
}

void LM75_write_Configuration(uint8_t Configuration_register)
{
	soft_IIC_Start();
	soft_write_address(0,IIC_address);
	soft_write_Byte(0x01);
	soft_write_Byte(Configuration_register);
	soft_IIC_Stop();
}

void LM75_write_Low_temperature_alarm(int Low_temperature_alarm)
{
	Low_temperature_alarm*=2;
	Low_temperature_alarm<<=7;
	soft_IIC_Start();
	soft_write_address(0,IIC_address);
	soft_write_Byte(0x02);
	soft_write_Byte(Low_temperature_alarm>>8);
	soft_write_Byte(Low_temperature_alarm);
	soft_IIC_Stop();
}

void LM75_write_High_temperature_alarm(int High_temperature_alarm)
{
	High_temperature_alarm*=2;
	High_temperature_alarm<<=7;
	soft_IIC_Start();
	soft_write_address(0,IIC_address);
	soft_write_Byte(0x03);
	soft_write_Byte(High_temperature_alarm>>8);
	soft_write_Byte(High_temperature_alarm);
	soft_IIC_Stop();
}



