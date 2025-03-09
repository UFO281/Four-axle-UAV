# 导入顶层 配置文件config.mk, 进而可以使用其定义的变量，例如BUILD_DIR，CFLAGS
include ../config.mk

# 获取当前目录下所有的 .c 文件，赋值给变量 SRCS
SRCS = $(wildcard *.c)

# 获取当前目录下所有的 .d 文件，赋值给变量 d_DIR
d_DIR = $(wildcard $(BUILD_DIR)/*.d)


# 将 当前目录下 所有.c 文件替换为 .o 文件放到 build 目录下
OBJS = $(SRCS:%.c= $(BUILD_DIR)/%.o)

# 默认目标：编译所有的 .c 文件为 .o 文件
all: $(OBJS)

# 如果目录不存在就创建他
$(shell mkdir -p $(BUILD_DIR))

# 编译规则：将 .c 文件编译为 build 目录下的 .o 文件
# $(BUILD_DIR)/%.o，BUILD_DIR变量下所有的.o文件,
# %.c，当前目录下所有的.c文件
$(BUILD_DIR)/%.o: %.c
# @echo "\n【66】PRO_DIR = $(PRO_DIR) \n"
# @echo "\n【77】INC_DIRS = $(INC_DIRS) \n"
# @echo "\n【88】I_INC_DIR = $(I_INC_DIR) \n"
	@echo "【661】$@ $< \n"
	@echo "【77】CFLAGS = $(CFLAGS) \n"
	$(CC) -c -o $@ $< $(CFLAGS)

# 清理生成的文件
clean:
	rm -f $(OBJS) $(d_DIR)