#include "bmpiic.h"
//#include "delay.h"
// 	#include "main.h"  
  //BMP IIC 延时函数
void delay_us(uint32_t us)
{

    uint32_t i;

    // 计时72节拍，默认时钟72M（对应1us）
    // 下次运行SysTick_Config时又会开启时钟
    SysTick_Config(72);

    for (i = 0; i < us; i++)
    {
        // 等待计数到0
        while (!((SysTick->CTRL) & SysTick_CTRL_COUNTFLAG_Msk));
    }

    // 关掉定时器
    SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);

}
void BMP_IIC_Delay(void)
{
	delay_us(8);
}

//初始化IIC
void BMP_IIC_Init(void)
{
//由CUBEMX生成	
 
}
//产生IIC起始信号
void BMP_IIC_Start(void)
{
	BMP_SDA_OUT();     //sda线输出
	BMP_IIC_SDA_SET;	  	  
	BMP_IIC_SCL_SET;
	BMP_IIC_Delay();
 	BMP_IIC_SDA_RESET;//START:when CLK is high,DATA change form high to low 
	BMP_IIC_Delay();
	BMP_IIC_SCL_RESET;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void BMP_IIC_Stop(void)
{
	BMP_SDA_OUT();//sda线输出
	BMP_IIC_SCL_RESET;
	BMP_IIC_SDA_RESET;//STOP:when CLK is high DATA change form low to high
 	BMP_IIC_Delay();
	BMP_IIC_SCL_SET;  
	BMP_IIC_SDA_SET;//发送I2C总线结束信号
	BMP_IIC_Delay();							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 BMP_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	BMP_SDA_IN();      //SDA设置为输入  
	BMP_IIC_SDA_SET;delay_us(4);	   
	BMP_IIC_SCL_SET;delay_us(4);	 
	while(BMP_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			BMP_IIC_Stop();
			return 1;
		}
	}
	BMP_IIC_SCL_RESET;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void BMP_IIC_Ack(void)
{
	BMP_IIC_SCL_RESET;
	BMP_SDA_OUT();
	BMP_IIC_SDA_RESET;
	BMP_IIC_Delay();
	BMP_IIC_SCL_SET;
	BMP_IIC_Delay();
	BMP_IIC_SCL_RESET;
}
//不产生ACK应答		    
void BMP_IIC_NAck(void)
{
	BMP_IIC_SCL_RESET;
	BMP_SDA_OUT();
	BMP_IIC_SDA_SET;
	BMP_IIC_Delay();
	BMP_IIC_SCL_SET;
	BMP_IIC_Delay();
	BMP_IIC_SCL_RESET;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void BMP_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	BMP_SDA_OUT(); 	    
    BMP_IIC_SCL_RESET;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {          
				if(((txd&0x80)>>7))
				{
					BMP_IIC_SCL_SET;
				}
				else
				{
					BMP_IIC_SCL_RESET;
				}

        txd<<=1; 
		BMP_IIC_Delay(); 				
		BMP_IIC_SCL_SET;
		BMP_IIC_Delay(); 
		BMP_IIC_SCL_RESET;	
		BMP_IIC_Delay();
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 BMP_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	BMP_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        BMP_IIC_SCL_RESET; 
        BMP_IIC_Delay();
		BMP_IIC_SCL_SET;
        receive<<=1;
        if(BMP_READ_SDA)receive++;   
		BMP_IIC_Delay(); 
    }					 
    if (!ack)
        BMP_IIC_NAck();//发送nACK
    else
        BMP_IIC_Ack(); //发送ACK   
    return receive;
}


















