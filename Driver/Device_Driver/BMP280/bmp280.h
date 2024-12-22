/**
 * @file bmp280.h
 * @author wls (ufo281@outlook.com) 
 * @brief 
 * @version 1.0
 * @date 2024-12-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

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

#if 0
/* use example

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /*
    OLED接线： 				A0//SCL
                                        A1//SDA
                                        A5//RES
                                        A6//DC
                                        A4//CS

    BMP280接线：				B7//SDA
                                        B6//SCL

    串口接线：					A10//RX
                                        A9//TX

    测高功能按键：     B3//B3连（1K-10K电阻）连 按键 连 GND

    */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_I2C1_Init();
    /* USER CODE BEGIN 2 */
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

    Bmp280Init();
    OLED_Init();
    OLED_ColorTurn(0);   // 0正常显示，1 反色显示
    OLED_DisplayTurn(0); // 0正常显示 1 屏幕翻转显示
    uint8_t st[255] = {0};
    extern double basepress;

    while (1)
    {

        printf("ok:%d\r\n", bmp280_GetValue());
        printf("temp:%lf\r\n", bmp280_GetTEMPERATURE());
        printf("air_p:%lf\r\n", bmp280_Get_P());
        printf("highth:%f\r\n", bmp280_GetAltitude());

        sprintf((char *)st, "T:%.3lf", bmp280_GetTEMPERATURE());
        OLED_ShowString(10, 0, st, 16, 1);
        sprintf((char *)st, "P:%.3lf", bmp280_Get_P());
        OLED_ShowString(10, 16, st, 16, 1);
        sprintf((char *)st, "H:%.3lf", bmp280_GetAltitude());
        OLED_ShowString(10, 32, st, 16, 1);

        // 按动按键设置该位置气压为基准值，可以测量高度。
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET)
            basepress = bmp280_Get_P();

        sprintf((char *)st, "baseP:%.3lf", basepress);
        OLED_ShowString(10, 48, st, 16, 1);
        OLED_Refresh(); // OLED刷新

        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(1000);

        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

*/
#endif