# 定义编译器
CC = gcc

# 项目路径
PRO_DIR = /home/wls/git/four-axle-uav

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


# 定义生成的可执行文件目录&& bin hex file
BIN_DIR = $(PRO_DIR)/bin


# 定义编译选项（C 编译器的参数）
# 说明：
#   -Wall：启用所有常见的编译警告，帮助发现潜在错误
#   -Wextra：启用额外的警告信息，比 -Wall 更严格
#   -O2：启用优化级别 2，提高运行效率（比 -O1 更优化，但不影响调试）
#   -I $(INC_DIR)：指定头文件目录（$(INC_DIR) 变量应包含头文件路径）
#   -fdiagnostics-color=always：让 GCC 在终端输出彩色警告/错误信息，提升可读性
#   -Werror：将所有警告视为错误（如果有警告就无法编译）
#   -g：生成调试信息，方便调试程序
#   -std=c99：使用 C99 标准进行编译
#   -DDEBUG：定义 DEBUG 宏，用于条件编译
CFLAGS := -Wall \
         -Wextra \
         -O2 \
		 $(I_INC_DIR) \
         -fdiagnostics-color=always \
		 -g \
		 -std=c99 \
		 -DDEBUG \
		 -Werror \