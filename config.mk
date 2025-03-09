# 定义编译器
CC = arm-none-eabi-gcc

# 项目路径
PRO_DIR = /home/wls/git/four-axle-uav

# 编译生成目标文件目录
BUILD_DIR = $(PRO_DIR)/build


# 定义生成的可执行文件目录&& bin hex file
BIN_DIR = $(PRO_DIR)/bin

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


#-------------------CFLAGS(compile options)--------------------------------------------

# -I 自动添加头文件路径
I_INC_DIR = $(foreach dir, $(INC_DIRS), -I $(dir))

# cpu
CPU = -mcpu=cortex-m3

# mcu 编译选项
# $(CPU)  指定 CPU 架构（通常是 -mcpu=cortex-mX）
# -mthumb  生成 Thumb 指令集代码（Cortex-M 处理器只支持 Thumb 指令集）
# $(FPU)  指定 FPU 相关参数（由外部变量定义）
# $(FLOAT-ABI)  指定浮点 ABI（通常是 -mfloat-abi=soft 或 -mfloat-abi=hard）
# -mfloat-abi=soft  使用软件浮点运算（Cortex-M3 没有硬件 FPU，使用软件实现）
# -mfpu=fpv4-sp-d16  指定 FPU 类型（仅适用于有 FPU 的 Cortex-M4/M7，Cortex-M3 可忽略）
# -ffunction-sections  每个函数放入独立的代码段，支持链接时删除未使用的函数（减少 ROM 占用）
# -fdata-sections  每个变量放入独立的数据段，支持链接时删除未使用的数据（减少 RAM 占用）
# -fno-common  禁止重复定义全局变量（防止链接时多个 `int x;` 变量冲突）
# -fmessage-length=0  让 GCC 在终端输出完整错误信息，不换行，便于查看完整日志
# -fno-builtin  禁用标准库函数（如 `memcpy`、`strlen` 等），适用于裸机开发（无标准库）
# -ffreestanding  指定代码为 **独立环境**，不依赖标准库（适用于裸机或 RTOS）
# -fno-strict-aliasing  关闭严格别名优化，避免不同类型指针转换导致的优化问题
# -fshort-enums  让 `enum` 类型占用最小的字节数，而不是默认的 `int`（减少内存占用）
# -gdwarf-2  生成 DWARF v2 调试信息（用于 GDB 调试）
# -MMD  生成 `.d` 依赖文件（跟踪 `#include` 头文件）
# -MP  生成空规则，防止头文件删除导致 `make` 失败
# -MF"$(@:%.o=%.d)"  指定 `.d` 依赖文件的路径（`.o` → `.d）
MCU_C = $(CPU) \
		-mthumb \
		-ffunction-sections\
		-fdata-sections\
		-fno-common\
		-fmessage-length=0\
		-fno-strict-aliasing\
		-fshort-enums\
		-gdwarf-2\
		-MMD \
		-MP 
# $(FPU) \
# $(FLOAT-ABI) \
# -mfloat-abi=soft\
# -mfpu=fpv4-sp-d16\
# -MF"$(@:%.o=%.d)"


# 定义编译选项（C 编译器的参数）
# 说明：
#   -Wall：启用所有常见的编译警告，帮助发现潜在错误
#   -Wextra：启用额外的警告信息，比 -Wall 更严格
# -O0	关闭所有优化，调试最直观，代码执行慢	调试阶段
# -Og	适当优化，但保证调试友好	嵌入式调试
# -O1	轻量优化，提升性能，仍适合调试	一般优化
# -O2	更高级优化，提高运行效率，但影响调试	正式发布
# -O3	激进优化，最大化性能，可能影响稳定性	高性能应用
#   -I $(INC_DIR)：指定头文件目录（$(INC_DIR) 变量应包含头文件路径）
#   -fdiagnostics-color=always：让 GCC 在终端输出彩色警告/错误信息，提升可读性
#   -Werror：将所有警告视为错误（如果有警告就无法编译）
#   -g：生成调试信息，方便调试程序
#   -std=c99：使用 C99 标准进行编译
#   -DDEBUG：定义 DEBUG 宏，用于条件编译
CFLAGS := -Wall \
         -Wextra \
         -Og \
         -fdiagnostics-color=always \
		 -g \
		 -std=c99 \
		 -DDEBUG \
		 -Werror \
		 $(MCU_C)\
		 $(I_INC_DIR) 

#-------------------CFLAGS(compile options)--------------------------------------------