#include "aht10.h"
#include "delay.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "IIC.h"


/**
brief AHT10初始化函数
param NONE
return NONE
*/
void AHT10Init()
{
    IIC_Init();
    IIC_Start();
    IIC_Send_Data_Byte(AHT10_ADDRESS);
    IIC_Send_Data_Byte(0xe1);
    IIC_Send_Data_Byte(0x08);
    IIC_Send_Data_Byte(0x00);
    IIC_Stop();
    Delay_ms(40); // 延时20ms让传感器稳定
}

/**
brief 检查AHT10是否存在
param NONE
return 0存在  1不存在
*/
u8 AHT10Check(void)
{
    u8 ack = 0;
    IIC_Start();
    IIC_Send_Data_Byte(AHT10_ADDRESS);
    ack = IIC_Wait_ACK();
    IIC_Stop();
    return ack;
}

/**
brief AHT10软复位
param NONE
return NONE
*/
void AHT10Reset(void)
{
    IIC_Start();
    IIC_Send_Data_Byte(AHT10_WRITE);
    IIC_Wait_ACK();
    IIC_Send_Data_Byte(0xba);
    IIC_Wait_ACK();
    IIC_Stop();
}

/**
brief 检查AHT10读温湿度数据
param *temperature：需要读出的温度数据，float指针类型,精度范围+-0.3C
param *humidity：需要读出的湿度数据，u8指针类型,精度范围+-2RH
return 0 读数据正常 1读数据失败
*/
u8 AHT10ReadData(float *temperature, u8 *humidity)
{
    u8 ack;
    u32 SRH = 0, ST = 0;
    u8 databuff[6];
    IIC_Start();
    IIC_Send_Data_Byte(AHT10_WRITE);
    IIC_Wait_ACK();
    IIC_Send_Data_Byte(0xac);
    IIC_Wait_ACK();
    IIC_Send_Data_Byte(0x33);
    IIC_Wait_ACK();
    IIC_Send_Data_Byte(0x00);
    IIC_Wait_ACK();
    IIC_Stop();
    Delay_ms(80); // 延时一会等待数据读出
    IIC_Start();
    IIC_Send_Data_Byte(AHT10_READ);
    IIC_Wait_ACK();
    ack = IIC_Recive_Data_Byte(1);
    if ((ack & 0x40) == 0)
    {
        databuff[0] = IIC_Recive_Data_Byte(1);
        databuff[1] = IIC_Recive_Data_Byte(1);
        databuff[2] = IIC_Recive_Data_Byte(1);
        databuff[3] = IIC_Recive_Data_Byte(1);
        databuff[4] = IIC_Recive_Data_Byte(0);
        IIC_Stop();
        SRH = (databuff[0] << 12) + (databuff[1] << 4) + (databuff[2] >> 4);
        ST = ((databuff[2] & 0X0f) << 16) + (databuff[3] << 8) + (databuff[4]);
        *humidity = (int)(SRH * 100.0 / 1024 / 1024 + 0.5);
        *temperature = ((int)(ST * 2000.0 / 1024 / 1024 + 0.5)) / 10.0 - 50;
        return 0;
    }
    IIC_Stop();
    return 1;
}
