#ifndef __BMP280_H
#define __BMP280_H
 
        
#include <math.h>    
 #include "main.h"
 #include "stdio.h"
 #include "i2c.h"
typedef struct 
{
	double P;
	double T;
}Bmp280DataTypeDef;
 
extern Bmp280DataTypeDef Bmp280Data;
 
#define AddrWrite 0xEC // 从机地址+写信号  SDO默认接地
#define AddrRead 0xED // 从机地址+读取信号  0xEC+1
#define NumRestAddr 0XE0 // 数据复位地址
#define NumRestDate 0XB6 // 数据复位数据
	#ifndef delay_ms
	#define delay_ms(t) HAL_Delay(t)
	#endif


void Bmp280Init(void);
uint8_t bmp280_GetValue(void);
float bmp280_GetAltitude(void);
double bmp280_GetTEMPERATURE(void);
double bmp280_Get_P(void);

void bmp280_sleep();
void bmp280_wake();


























#endif


