#ifndef __OLED_H
#define __OLED_H 
//#include "gpio.h"
//#include "main.h"
#include "sys.h"
//#include "stdlib.h"	
//#include "stm32f10x.h"
//#include "stm32f1xx_hal.h"

#define GPIO_ResetBits(lgpio,lpin)  HAL_GPIO_WritePin(lgpio,lpin,GPIO_PIN_RESET)
#define GPIO_SetBits(lgpio,lpin) HAL_GPIO_WritePin(lgpio,lpin,GPIO_PIN_SET)

//#define GPIO_ResetBits(lgpio,lpin)  HAL_GPIO_WritePin(lgpio,lpin,GPIO_PIN_SET)
//#define GPIO_SetBits(lgpio,lpin) HAL_GPIO_WritePin(lgpio,lpin,GPIO_PIN_RESET)


#define GPIO_Pin_0 GPIO_PIN_0   
#define GPIO_Pin_1 GPIO_PIN_1   
#define GPIO_Pin_5 GPIO_PIN_5  
#define GPIO_Pin_6 GPIO_PIN_6  
#define GPIO_Pin_4 GPIO_PIN_4 
	#ifndef delay_ms
	#define delay_ms(t) HAL_Delay(t)
	#endif
	
//-----------------OLED端口定义---------------- 

#define OLED_SCL_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_0)//SCL
#define OLED_SCL_Set() GPIO_SetBits(GPIOA,GPIO_Pin_0)

#define OLED_SDA_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_1)//SDA
#define OLED_SDA_Set() GPIO_SetBits(GPIOA,GPIO_Pin_1)

#define OLED_RES_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_5)//RES
#define OLED_RES_Set() GPIO_SetBits(GPIOA,GPIO_Pin_5)

#define OLED_DC_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_6)//DC
#define OLED_DC_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_6)
 		     
#define OLED_CS_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_4)//CS
#define OLED_CS_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_4)



#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);
void OLED_ShowChar6x8(u8 x,u8 y,u8 chr,u8 mode);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);
void OLED_ScrollDisplay(u8 num,u8 space,u8 mode);
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);
void OLED_Init(void);

#endif

