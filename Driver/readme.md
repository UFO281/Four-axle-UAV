Driver(驱动层项目代码文件):
+ Core :ARM Coretex-M内核代码

+ Peripheral_Driver_Lib:内核外设驱动库（eg: IIC SPI UART CAN USB MAC....）

+ Peripheral_Driver：外设驱动+协议层驱动（例如：PWM TIMER IIC SPI CAN UART ADC USB MAC ...外设驱动+SPI/IIC/CAN/UART等协议层驱动（包含软件模拟协议驱动） ）

+ Dev_Driver:设备驱动代码，例如:姿态角度传感器MPU6050的驱动程序，温湿度传感器AHT10的驱动程序等等。

    
