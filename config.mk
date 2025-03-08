# 定义编译器
CC = gcc

PRO_DIR = /home/wls/git/four-axle-uav

INC_DIRS =  APP 
# Driver/Core \
			# Driver/Device_Driver/AHT10 \
			# Driver/Device_Driver/BMP280 \
			# Driver/Device_Driver/LED \
			# Driver/Device_Driver/MPU6050 \
			# Driver/Device_Driver/MPU6050/eMPL \
			# Driver/Peripheral_Driver/Delay \
			# Driver/Peripheral_Driver/IIC \
			# Driver/Peripheral_Driver/SPI \
			# Driver/Peripheral_Driver/Uart \
			# Driver/Peripheral_Driver_Lib/Include 

INC_DIR = $(foreach dir, $(INC_DIRS), $(PRO_DIR) / @echo $(dir))


I_INC_DIR = $(foreach dir, $(INC_DIRS), -I $(dir))



# 项目路径

# 头文件包含目录
INC_DIR = $(PRO_DIR)/Driver/inc

# 编译生成目标文件目录
BUILD_DIR = $(PRO_DIR)/build

# 定义编译选项
CFLAGS = -Wall -Wextra -O2 $(I_INC_DIR)

BIN_DIR = $(PRO_DIR)/bin


