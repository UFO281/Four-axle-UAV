/**
 * @file main.c
 * @author wls (ufo281@outlook.com) 
 * 
 * @brief bootloader branch
 * 
 * @version 1.0
 * @date 2024-09-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "stm32f10x.h"                  
#include "Delay.h"
#include "usart.h"



int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    Usart1_Init();

	while (1)
	{

		GPIO_WriteBit(GPIOA, GPIO_Pin_0, (BitAction)0);
		Delay_ms(100);
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, (BitAction)1);
		Delay_ms(100);

        printf("hello world! \r\n");
	}
}
