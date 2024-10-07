/**
 * @file main.c
 * @author wls (ufo281@outlook.com)
 *
 * @brief this is DC motor four rotor UAV
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
#include "LED.h"
#include "mpu6050.h"
#include "aht10.h"


int main(void)
{
    Usart1_Init();
    LED_Init();

    AHT10Init(); // 温湿度传感器初始化  SCL:PB3 SDA:PB4
    AHT10Reset();

    MPU_Init(); // 初始化MPU6050 SCL:PB10  SDA:PB11

    if (mpu_dmp_init() != 0)
    {
        printf("mpu6050 dmp init failed!\r\n");
    }

    float pitch, roll, yaw;    // 欧拉角
    short aacx, aacy, aacz;    // 加速度传感器原始数据
    short gyrox, gyroy, gyroz; // 陀螺仪原始数据

    float AHT10_temp = 0; // 检测到的温度数据
    u8 AHT10_humi = 0;    // 检测到的湿度数据

    int i = 2;
    while (1)
    {
        // LED1_ON();
        // Delay_ms(100);
        // LED1_OFF();
        Delay_ms(100);

        AHT10ReadData(&AHT10_temp, &AHT10_humi); // 读取温湿度数据

        printf("Temp:%dC  Humi:%d  \r\n",
               (int)AHT10_temp,
               AHT10_humi);

#if 1                                               /*Get MPU6050 data*/
        MPU_Get_Accelerometer(&aacx, &aacy, &aacz); // 得到加速度传感器数据 X Y Z加速度数据
        MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);  // 得到陀螺仪数据 X Y Z角速度数据
        mpu_dmp_get_data(&pitch, &roll, &yaw);      // 得到俯仰角pitch，和翻滚角roll，yaw航向角数据
#endif                                              /*Get MPU6050 data*/

        printf("MPU6050 pitch:%d roll:%d yaw:%d \r\n",
               (int)pitch, (int)roll, (int)yaw);

        printf("hello world! %d \r\n", i++);
    }
}
