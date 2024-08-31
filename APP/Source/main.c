/**
 * @file main.c
 * @author wls (ufo281@outlook.com) 
 * @brief 
 * @version 1.0
 * @date 2024-08-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "STC12CXX.h"
#include "pwm.h"
#include "uart.h"
#include "intrins.h"



/**
 * @brief 硬件初始化 包含设备初始化，
 *       以及内核外设PWM TIMER IIC...初始化
 * 
 */
void hardware_init(void)
{

    uart1_init();
    pwm_init();

}


/**
 * @brief delay x us
 * 
 * @11.0592MHz
 * 
 * @param x 
 */
void Delay_xus(unsigned int x)	
{
    while (x--)
    {
    	_nop_();
    }
    
}



/**
 * @brief 
 * 
 * @11.0592MHz 
 * 
 */
void Delay_1ms(void)
{
	unsigned char data i, j;

	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}



/**
 * @brief delay x ms
 * 
 * @param x 
 */
void delay_xms(unsigned int x)
{

    while (x--)
    {
        Delay_1ms();
    }
    
}



void delay_xs(void)
{

    delay_xms(1000);
    
}



/**
 * @brief 
 * 
 */
void main(void)
{

    hardware_init();

    while (1)
    {

        SendString("STC12C5A60S2\r\nUart Test !\r\n");

    }
    

}

