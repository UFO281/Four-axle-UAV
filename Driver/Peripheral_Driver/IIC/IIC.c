/**
 * @file IIC.c
 * @author wls (ufo281@outlook.com)
 * @brief
 * @version 1.0
 * @date 2024-10-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "IIC.h"
// #include "stm32f10x_i2c.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "delay.h"

#ifdef HardWare_IIC /*----Hard ware IIC-----*/

ErrorStatus H_IIC_Checkevent(I2C_TypeDef *I2Cx, uint32_t I2C_EVENT)
{
}

/**
 * @brief hard ware IIC Init
 *
 */
void H_IIC_Init(void)
{
}

void H_IIC_Sart(void)
{
}

/**
 * @brief Hard ware IIC send 1 Byte data
 *
 */
void H_IIC_Send_Data(unsigned char data)
{
}

/**
 * @brief IIC RX 1Byte DATA
 *
 * @return unsigned char IIC recived 1byte data
 */
unsigned char H_IIC_Recive_Data(void)
{
}

/**
 * @brief hard ware iic send iic device address
 *
 * @param Addr IIC SLAVE DEVICE ADDRESS
 *
 * @param flag WRITE OR READ FLAG(I2C_Direction_Transmitter/I2C_Direction_Receiver)
 */
void H_IIC_Send_Addr(unsigned char Addr, unsigned char flag)
{
}

/**
 * @brief hard ware iic ack signal
 *
 */
void H_IIC_ACK(void)
{
}

/**
 * @brief hard ware iic not ack signal
 *
 */
void H_IIC_NotACK(void)
{
}

void H_IIC_Stop(void)
{
}

#endif /*----Hard ware IIC-----*/

#ifdef SoftWare_IIC /*----Soft IIC-----*/

/**
 * 函    数：I2C写SCL引脚电平
 * 参    数：BitValue 协议层传入的当前需要写入SCL的电平，范围0~1
 * 返 回 值：无
 * 注意事项：此函数需要用户实现内容，当BitValue为0时，需要置SCL为低电平，当BitValue为1时，需要置SCL为高电平
 */
void S_IIC_W_SCL(unsigned char BitValue)
{
    // 根据BitValue，设置SCL引脚的电平
    GPIO_WriteBit(GPIOB, GPIO_Pin_3, (BitAction)BitValue);

    // 延时10us，防止时序频率超过要求
    Delay_us(10);
}

/**
 * 函    数：S_IIC写SDA引脚电平
 * 参    数：BitValue 协议层传入的当前需要写入SDA的电平，范围0~0xFF
 * 返 回 值：无
 * 注意事项：此函数需要用户实现内容，当BitValue为0时，需要置SDA为低电平，当BitValue非0时，需要置SDA为高电平
 */
void S_IIC_W_SDA(unsigned char BitValue)
{
    // 根据BitValue，设置SDA引脚的电平，BitValue要实现非0即1的特性
    GPIO_WriteBit(GPIOB, GPIO_Pin_4, (BitAction)BitValue);

    // 延时10us，防止时序频率超过要求
    Delay_us(10);
}

/**
 * 函    数：S_IIC读SDA引脚电平
 * 参    数：无
 * 返 回 值：协议层需要得到的当前SDA的电平，范围0~1
 * 注意事项：此函数需要用户实现内容，当前SDA为低电平时，返回0，当前SDA为高电平时，返回1
 */
unsigned char S_IIC_R_SDA(void)
{
    unsigned char BitValue;

    // 读取SDA电平
    BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4);

    // 延时10us，防止时序频率超过要求
    Delay_us(10);

    // 返回SDA电平
    return BitValue;
}

/**
 * @brief soft IIC Init
 *      SCL:PB3
 *      SDA:PB4
 *
 */
void S_IIC_Init(void)
{
    /*开启时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
    /*PB3 PB4 为JTAG的IO 所以需要禁止JATG 否则用不了PB3 PB4*/
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    /*GPIO初始化*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4; /*SCL:PB3*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*设置默认电平*/
    GPIO_SetBits(GPIOB, GPIO_Pin_3 | GPIO_Pin_4); // PB6,PB7 输出高
}

/**
 * @brief 软件模拟IIC 产生IIC起始信号
 *
 */
void S_IIC_Start(void)
{
    // 释放SDA，确保SDA为高电平
    S_IIC_W_SDA(1);

    // 释放SCL，确保SCL为高电平
    S_IIC_W_SCL(1);

    // 在SCL高电平期间，拉低SDA，产生起始信号
    S_IIC_W_SDA(0);

    // 起始后把SCL也拉低，即为了占用总线，也为了方便总线时序的拼接
    S_IIC_W_SCL(0);
}

/**
 * @brief 产生IIC停止信号
 *
 */
void S_IIC_Stop(void)
{

    // 拉低SDA，确保SDA为低电平
    S_IIC_W_SDA(0);

    // 释放SCL，使SCL呈现高电平
    S_IIC_W_SCL(1);

    // 在SCL高电平期间，释放SDA，产生终止信号
    S_IIC_W_SDA(1);
}

/**
 * @brief wait IIC ack signal
 *
 * @return unsigned char 0:OK,ACK
 *                       1:Failed! NOT ACK
 */
unsigned char S_IIC_Wait_Ack(void)
{
    // 定义应答位变量
    unsigned char AckBit;

    // 接收前，主机先确保释放SDA，避免干扰从机的数据发送
    S_IIC_W_SDA(1);

    // 释放SCL，主机机在SCL高电平期间读取SDA
    S_IIC_W_SCL(1);

    // 将应答位存储到变量里
    AckBit = S_IIC_R_SDA();

    // 拉低SCL，开始下一个时序模块
    S_IIC_W_SCL(0);

    // 返回定义应答位变量
    return AckBit;
}

/**
 * @brief SOFT IIC SEND ACK SIGNAL
 *
 */
void S_IIC_ACK(void)
{
    // 主机把应答位数据放到SDA线
    S_IIC_W_SDA(0);

    // 释放SCL，从机在SCL高电平期间，读取应答位
    S_IIC_W_SCL(1);

    // 拉低SCL，开始下一个时序模块
    S_IIC_W_SCL(0);
}

/**
 * @brief IIC SEND NOT ACK
 *
 */
void S_IIC_NACK(void)
{
    // 主机把应答位数据放到SDA线
    S_IIC_W_SDA(1);

    // 释放SCL，从机在SCL高电平期间，读取应答位
    S_IIC_W_SCL(1);

    // 拉低SCL，开始下一个时序模块
    S_IIC_W_SCL(0);
}

/**
 * @brief Software simulation IIC Send a Byte
 *
 * @param data
 */
void S_IIC_Send_Byte(unsigned char data)
{
    unsigned char i;

    // 循环8次，主机依次发送数据的每一位
    for (i = 0; i < 8; i++)
    {
        // 使用掩码的方式取出Byte的指定一位数据并写入到SDA线
        S_IIC_W_SDA(data & (0x80 >> i));

        // 释放SCL，从机在SCL高电平期间读取SDA
        S_IIC_W_SCL(1);

        // 拉低SCL，主机开始发送下一位数据
        S_IIC_W_SCL(0);
    }
}

/**
 * @brief IIC READ A BYTE DATA
 *
 * @param ack 1:send ack signal
 *            0:send not ack signal
 *
 * @return unsigned char: IIC RX A BYTE DATA
 */
unsigned char S_IIC_Read_Byte(unsigned char ack)
{

    // 定义接收的数据，并赋初值0x00，此处必须赋初值0x00，后面会用到
    unsigned char i, Byte = 0x00;

    // 接收前，主机先确保释放SDA，避免干扰从机的数据发送
    S_IIC_W_SDA(1);

    // 循环8次，主机依次接收数据的每一位
    for (i = 0; i < 8; i++)
    {
        // 释放SCL，主机机在SCL高电平期间读取SDA
        S_IIC_W_SCL(1);

        // 读取SDA数据，并存储到Byte变量
        if (S_IIC_R_SDA() == 1)
        {
            Byte |= (0x80 >> i);
        }

        S_IIC_W_SCL(0); // 拉低SCL，从机在SCL低电平期间写入SDA
    }

    if (!ack)
        S_IIC_NACK(); // 发送nACK
    else
        S_IIC_ACK(); // 发送ACK

    // 返回接收到的一个字节数据
    return Byte;
}

#endif /*----Soft IIC-----*/
