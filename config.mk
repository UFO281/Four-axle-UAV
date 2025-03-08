# 定义编译器
CC = gcc

# 项目路径
PRO_DIR = /home/wls/stm32/four-axle-uav

# 头文件包含目录
INC_DIRS =  $(PRO_DIR)/APP \
			$(PRO_DIR)/Driver/Core \
			$(PRO_DIR)/Driver/Device_Driver/AHT10 \
			$(PRO_DIR)/Driver/Device_Driver/BMP280 \
			$(PRO_DIR)/Driver/Device_Driver/LED \
			$(PRO_DIR)/Driver/Device_Driver/MPU6050 \
			$(PRO_DIR)/Driver/Device_Driver/MPU6050/eMPL \
			$(PRO_DIR)/Driver/Peripheral_Driver/Delay \
			$(PRO_DIR)/Driver/Peripheral_Driver/IIC \
			$(PRO_DIR)/Driver/Peripheral_Driver/SPI \
			$(PRO_DIR)/Driver/Peripheral_Driver/Uart \
			$(PRO_DIR)/Driver/Peripheral_Driver_Lib/Include 

# -I 自动添加头文件路径
I_INC_DIR = $(foreach dir, $(INC_DIRS), -I $(dir))


# 编译生成目标文件目录
BUILD_DIR = $(PRO_DIR)/build

# 定义编译选项
CFLAGS = -Wall -Wextra -O2 $(I_INC_DIR)

# 定义生成的可执行文件目录&& bin hex file
BIN_DIR = $(PRO_DIR)/bin


