#include<ds18b20.h>


/*Ds18b20复位*/
void Init_Ds18b20()
{	 
      u8 i=0;
	 /*设置IO口为输出模式*/
     Gpio_Config_Mode_Out();

	 /*拉低总线*/ 
     DS18B20_DQ_OUT_Low;

	 /*延迟480us*/
	 Delay_us(480);
	 /*释放总线*/
	 DS18B20_DQ_OUT_High;

	 /*设置IO口为输入模式*/
	 Gpio_Config_FLOATING_In();

	 /*等待复位信号 注意不能无限等待*/
	 while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)&&(i<200))
	 i++;
}

/*写一个字节*/
void Write_one_byte(u8 a)
{
     u8 i=0;
	 u8 b=0x01;
	 u8 c=0;
	/*设置IO口为输出模式*/
    Gpio_Config_Mode_Out();
	
	for(i=0;i<8;i++)
	{
	     c=b&a;
		 if(c)
		 {
		       /*拉低总线*/
		     DS18B20_DQ_OUT_Low;
			 /*延迟15us产生写时隙*/
			 Delay_us(15);
			 /*释放总线*/
			 DS18B20_DQ_OUT_High;
			 /*保持40us*/
			 Delay_us(40);
		 }   
		 else
		 {
			 /*拉低总线*/
		     DS18B20_DQ_OUT_Low;
			 /*至少保持60us低电平*/	
			 Delay_us(60);
			 /*释放总线*/
			 DS18B20_DQ_OUT_High;

		 }
		 b=b<<1;  
	}
	     /*释放总线*/
	DS18B20_DQ_OUT_High;
}

/*读一个字节*/
u8 Read_one_byte()
{
	u8 a=0;
  	u8 i=0;      
	for(i=0;i<8;i++)
	{
	    /*设置IO口为输出模式*/ 
	    Gpio_Config_Mode_Out();
	    /*拉低总线*/
	    DS18B20_DQ_OUT_Low;
	    /*延迟1us产生读时隙*/
	    Delay_us(1);
	    /*释放总线*/
	    DS18B20_DQ_OUT_High;
	    /*设置IO口为浮空输入模式*/
	    Gpio_Config_FLOATING_In();

	    if(DS18B20_DQ_IN)
	    {
	      a=a>>1;
		  a=a|0x80;
	    }
	    else
	    {
	   	  a=a>>1;
	    }
		/*延迟50us保证时间要求*/
		Delay_us(50);
		/*设置IO口为输出模式*/ 
	    Gpio_Config_Mode_Out();
		/*释放总线*/
	    DS18B20_DQ_OUT_High;
    }
	return(a);
}


/***************
  温度获取子函数
  入口参数: 无
  出口参数: 温度
****************/
u8 wen_du_huo_qu()
{
   u16 a1=0;
	 u8 b=0;

	 /*复位DS18B20*/
	 Init_Ds18b20();
	 /*写跳过ROM指令*/
	 Write_one_byte(0xCC);
	 /*写温度转换指令*/
	 Write_one_byte(0x44);
	 /*延迟等待转换完成*/
	 Delay_us(20);
	 /*写读暂存器指令*/
	 Write_one_byte(0xBE);
	 /*读低八位*/
	 b=Read_one_byte();
	 /*读高八位*/
	 a1=Read_one_byte();
	 /*把高八位和低八位组合成16位*/
	 a1=a1<<8;
	 a1=a1+b;
	 a1=(u16)(a1*0.0625); 
	 return(a1);
}

