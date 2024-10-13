#include "aht10.h"
#include "delay.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "IIC.h"

/**
 * @brief IIC等待事件
 *
 * @param I2Cx I2C1 OR I2C2
 * @param I2C_EVENT
 * @return unsigned char 0:OK
 *                       1:Failed!
 */
unsigned char IIC_WaitEvent(I2C_TypeDef *I2Cx, uint32_t I2C_EVENT)
{
    uint32_t Timeout;

    // 给定超时计数时间
    Timeout = 10000;

    // 循环等待指定事件
    while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS)
    {
        Timeout--;        // 等待时，计数值自减
        if (Timeout == 0) // 自减到0后，等待超时
        {
            /*超时的错误处理代码，可以添加到此处*/
            // 跳出等待，不等了
            return 1;
        }
    }

    if (I2C_CheckEvent(I2Cx, I2C_EVENT) == SUCCESS)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
brief AHT10初始化函数
param NONE
return NONE
*/
void AHT10Init()
{

    // IIC_Init();
    // IIC_Start();
    // IIC_Send_Data_Byte(AHT10_ADDRESS);
    // IIC_Send_Data_Byte(0xe1);
    // IIC_Send_Data_Byte(0x08);
    // IIC_Send_Data_Byte(0x00);
    // IIC_Stop();

    Delay_ms(40); // 延时40ms让传感器稳定,官方规定

    // 开启I2C1的时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

    // 开启GPIOB的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /*GPIO初始化*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Pin = IIC_SDA_IO | IIC_SCL_IO;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    // 将PB6和PB7引脚初始化为复用开漏输出
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*I2C初始化*/
    // 定义结构体变量
    I2C_InitTypeDef I2C_InitStructure;

    // 模式，选择为I2C模式
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;

    // 时钟速度，选择为398KHz
    I2C_InitStructure.I2C_ClockSpeed = 300000;

    // 时钟占空比，选择Tlow/Thigh = 2
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;

    // 应答，选择使能
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;

    // 应答地址，选择7位，从机模式下才有效
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

    // 自身地址，从机模式下才有效
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;

    // 将结构体变量交给I2C_Init，配置I2C2
    I2C_Init(I2C1, &I2C_InitStructure);

    /*I2C使能*/
    I2C_Cmd(I2C1, ENABLE); // 使能I2C1，开始运行

    I2C_GenerateSTART(I2C1, ENABLE);                   // 硬件I2C生成起始条件
    IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT); // 等待EV5

    I2C_SendData(I2C1, AHT10_ADDRESS);                               // 硬件I2C发送寄存器地址
    IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED); // 等待EV6

    I2C_SendData(I2C1, 0xe1);                                // 硬件I2C发送寄存器地址
    IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING); // 等待EV8

    I2C_SendData(I2C1, 0x08);                                // 硬件I2C发送寄存器地址
    IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING); // 等待EV8

    I2C_SendData(I2C1, 0x00);                               // 硬件I2C发送数据
    IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED); // 等待EV8_2

    I2C_GenerateSTOP(I2C1, ENABLE); // 硬件I2C生成终止条件
}

/**
brief 检查AHT10是否存在
param NONE
return 0存在  1不存在
*/
u8 AHT10Check(void)
{
    u8 ack = 0;
    // IIC_Start();
    // IIC_Send_Data_Byte(AHT10_ADDRESS);
    // ack = IIC_Wait_ACK();
    // IIC_Stop();

    I2C_GenerateSTART(I2C1, ENABLE);                   // 硬件I2C生成起始条件
    IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT); // 等待EV5

    I2C_SendData(I2C1, AHT10_ADDRESS);                                     // 硬件I2C发送寄存器地址
    ack = IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED); // 等待EV6

    I2C_GenerateSTOP(I2C1, ENABLE); // 硬件I2C生成终止条件

    return ack;
}

/**
brief AHT10软复位
param NONE
return NONE
*/
void AHT10Reset(void)
{
    // IIC_Start();
    // IIC_Send_Data_Byte(AHT10_WRITE);
    // IIC_Wait_ACK();
    // IIC_Send_Data_Byte(0xba);
    // IIC_Wait_ACK();
    // IIC_Stop();

    I2C_GenerateSTART(I2C1, ENABLE);                   // 硬件I2C生成起始条件
    IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT); // 等待EV5

    I2C_SendData(I2C1, AHT10_WRITE);                                 // 硬件I2C发送寄存器地址
    IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED); // 等待EV8

    I2C_SendData(I2C1, 0xba);                               // 硬件I2C发送寄存器地址
    IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED); // 等待EV8_2

    I2C_GenerateSTOP(I2C1, ENABLE); // 硬件I2C生成终止条件
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
    uint8_t databuff[6];
    // IIC_Start();
    // IIC_Send_Data_Byte(AHT10_WRITE);
    // IIC_Wait_ACK();
    // IIC_Send_Data_Byte(0xac);
    // IIC_Wait_ACK();
    // IIC_Send_Data_Byte(0x33);
    // IIC_Wait_ACK();
    // IIC_Send_Data_Byte(0x00);
    // IIC_Wait_ACK();
    // IIC_Stop();

    I2C_GenerateSTART(I2C1, ENABLE);                   // 硬件I2C生成起始条件
    IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT); // 等待EV5

    I2C_SendData(I2C1, AHT10_WRITE);                                 // 硬件I2C发送寄存器地址
    IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED); // 等待EV6

    I2C_SendData(I2C1, 0xac);                                // 硬件I2C发送寄存器地址
    IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING); // 等待EV8

    I2C_SendData(I2C1, 0x33);                                // 硬件I2C发送寄存器地址
    IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING); // 等待EV8

    I2C_SendData(I2C1, 0x00);                               // 硬件I2C发送数据
    IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED); // 等待EV8_2

    I2C_GenerateSTOP(I2C1, ENABLE); // 硬件I2C生成终止条件

    Delay_ms(80); // 延时一会等待数据读出

    // IIC_Start();
    // IIC_Send_Data_Byte(AHT10_READ);
    // IIC_Wait_ACK();

    I2C_GenerateSTART(I2C1, ENABLE);                   // 硬件I2C生成起始条件
    IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT); // 等待EV5

    I2C_SendData(I2C1, AHT10_READ);                                  // 硬件I2C发送寄存器地址
    IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED); // 等待EV6

    // ack = IIC_Recive_Data_Byte(1);
    IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED); // 等待EV7
    ack = I2C_ReceiveData(I2C1);                         // 接收数据寄存器
    I2C_AcknowledgeConfig(I2C1, ENABLE);                 // 将应答恢复为使能，为了不影响后续可能产生的读取多字节操作

    if ((ack & 0x40) == 0)
    {
        printf("AHT10ReadData  ERROR! \r\n");
        // databuff[0] = IIC_Recive_Data_Byte(1);
        // databuff[1] = IIC_Recive_Data_Byte(1);
        // databuff[2] = IIC_Recive_Data_Byte(1);
        // databuff[3] = IIC_Recive_Data_Byte(1);
        // databuff[4] = IIC_Recive_Data_Byte(0);
        // IIC_Stop();

        IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED); // 等待EV7
        databuff[0] = I2C_ReceiveData(I2C1);                         // 接收数据寄存器
        I2C_AcknowledgeConfig(I2C1, ENABLE);                 // 将应答恢复为使能，为了不影响后续可能产生的读取多字节操作

        IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED); // 等待EV7
        databuff[1] = I2C_ReceiveData(I2C1);                         // 接收数据寄存器
        I2C_AcknowledgeConfig(I2C1, ENABLE);                 // 将应答恢复为使能，为了不影响后续可能产生的读取多字节操作

        IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED); // 等待EV7
        databuff[2] = I2C_ReceiveData(I2C1);                         // 接收数据寄存器
        I2C_AcknowledgeConfig(I2C1, ENABLE);                 // 将应答恢复为使能，为了不影响后续可能产生的读取多字节操作

        IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED); // 等待EV7
        databuff[3] = I2C_ReceiveData(I2C1);                         // 接收数据寄存器
        I2C_AcknowledgeConfig(I2C1, ENABLE);                 // 将应答恢复为使能，为了不影响后续可能产生的读取多字节操作

        IIC_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED); // 等待EV7
        databuff[4] = I2C_ReceiveData(I2C1);                         // 接收数据寄存器
        I2C_AcknowledgeConfig(I2C1, DISABLE);  // 将应答恢复为使能，为了不影响后续可能产生的读取多字节操作

        I2C_GenerateSTOP(I2C1, ENABLE); // 硬件I2C生成终止条件

        SRH = (databuff[0] << 12) + (databuff[1] << 4) + (databuff[2] >> 4);
        ST = ((databuff[2] & 0X0f) << 16) + (databuff[3] << 8) + (databuff[4]);
        *humidity = (int)(SRH * 100.0 / 1024 / 1024 + 0.5);
        *temperature = ((int)(ST * 2000.0 / 1024 / 1024 + 0.5)) / 10.0 - 50;
        return 0;
    }

    // IIC_Stop();
    I2C_GenerateSTOP(I2C1, ENABLE); // 硬件I2C生成终止条件

    return 1;
}
