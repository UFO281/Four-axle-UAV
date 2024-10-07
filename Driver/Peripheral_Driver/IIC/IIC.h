/**
 * @file IIC.h
 * @author wls (ufo281@outlook.com)
 * @brief
 * @version 1.0
 * @date 2024-10-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef IIC_H
#define IIC_H

#include "stm32f10x.h"


#define IIC_SCL_IO     GPIO_Pin_10
#define IIC_SDA_IO     GPIO_Pin_11



// #define HardWare_IIC /*use hard ware iic*/

#define SoftWare_IIC    /*use soft ware iic*/


#ifdef HardWare_IIC /*----Hard ware IIC-----*/

#define IIC_Init    H_IIC_Init

#define IIC_Start   H_IIC_Sart

#define IIC_Send_Data_Byte  H_IIC_Send_Data

#define IIC_Send_Addr  H_IIC_Send_Addr

#define IIC_Recive_Data_Byte    H_IIC_Recive_Data

#define IIC_ACK     H_IIC_ACK

#define IIC_No_ACK  H_IIC_NotACK

#define IIC_Stop    H_IIC_Stop


#endif /*----Hard ware IIC-----*/




#ifdef SoftWare_IIC /*----Soft IIC-----*/

#define IIC_Init    S_IIC_Init

#define IIC_Start   S_IIC_Start

#define IIC_Send_Data_Byte  S_IIC_Send_Byte

#define IIC_ACK     S_IIC_ACK

#define IIC_No_ACK   S_IIC_NACK

#define IIC_Recive_Data_Byte    S_IIC_Read_Byte

#define IIC_Stop    S_IIC_Stop

#define IIC_Wait_ACK    S_IIC_Wait_Ack


#endif /*----Soft IIC-----*/

void S_IIC_W_SCL(unsigned char BitValue);
void S_IIC_W_SDA(unsigned char BitValue);
unsigned char S_IIC_R_SDA(void);

void S_IIC_Init(void);  //初始化IIC的IO口				 
void S_IIC_Start(void);	//发送IIC开始信号
void S_IIC_Stop(void);	//发送IIC停止信号
void S_IIC_Send_Byte(unsigned char data);//IIC发送一个字节
unsigned char S_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
unsigned char S_IIC_Wait_Ack(void); //IIC等待ACK信号
void S_IIC_ACK(void);	//IIC发送ACK信号
void S_IIC_NACK(void);	//IIC不发送ACK信号

#endif
