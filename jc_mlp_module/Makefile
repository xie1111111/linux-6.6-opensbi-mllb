# 内核模块构建Makefile
obj-m += jc_mlp_module.o

# 内核源码目录（根据实际情况修改）
KERNEL_DIR ?= $(HOME)/autodl-tmp/linux-6.6

# 架构和交叉编译工具链
ARCH ?= riscv
CROSS_COMPILE ?= riscv64-unknown-linux-gnu-

# 编译选项：禁用优化以更好地调试
ccflags-y := -O0 -g

# 默认目标
all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

# 清理
clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) clean

# SCP传输
SCP_PORT ?= 2222
SCP_USER ?= ubuntu
SCP_HOST ?= localhost
REMOTE_DIR ?= /home/$(SCP_USER)/modules

scp-transfer: all
	@echo "通过SCP传输模块到 $(SCP_USER)@$(SCP_HOST):$(REMOTE_DIR)/ (端口:$(SCP_PORT))"
	scp -P $(SCP_PORT) jc_mlp_module.ko $(SCP_USER)@$(SCP_HOST):$(REMOTE_DIR)/
	@echo "✓ 传输完成"

.PHONY: all clean scp-transfer