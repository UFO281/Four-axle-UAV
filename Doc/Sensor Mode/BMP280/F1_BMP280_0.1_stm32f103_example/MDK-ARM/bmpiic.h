#ifndef __BMPIIC_H
#define __BMPIIC_H
//#include "sys.h" 
#include "main.h"
//IO方向设置


#define BMP_SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
#define BMP_SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}
//#define BMP_SDA_IN()  {GPIO_PORT_IIC -> MODER &= 0xffffff3f;}
//#define BMP_SDA_OUT() {GPIO_PORT_IIC -> MODER &= 0xffffff3f; GPIO_PORT_IIC -> MODER |= (uint32_t)(1 << 6);}
//IO操作函数	 
//#define BMP_IIC_SCL    PBout(10) 		//SCL
//#define BMP_IIC_SDA    PBout(11) 		//SDA	 
//#define BMP_READ_SDA   PBin(11) 		//输入SDA 


#define BMP_IIC_SCL_RESET   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET) 		//SCL
#define BMP_IIC_SDA_RESET   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET)	//SDA		 
#define BMP_IIC_SCL_SET     HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET)		//SCL
#define BMP_IIC_SDA_SET     HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_SET)		//SDA	 
#define BMP_READ_SDA    		HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)//输入SDA 
 

#define u8 uint8_t
//#define delay_us HAL_Delay
//IIC所有操作函数
void delay_us(uint32_t us);
void BMP_IIC_Delay(void);				//BMP IIC延时函数
void BMP_IIC_Init(void);                //初始化IIC的IO口				 
void BMP_IIC_Start(void);				//发送IIC开始信号
void BMP_IIC_Stop(void);	  			//发送IIC停止信号
void BMP_IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 BMP_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 BMP_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void BMP_IIC_Ack(void);					//IIC发送ACK信号
void BMP_IIC_NAck(void);				//IIC不发送ACK信号

#endif
















