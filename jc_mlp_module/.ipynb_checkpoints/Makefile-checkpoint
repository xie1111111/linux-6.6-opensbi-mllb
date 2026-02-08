# 内核模块构建Makefile - 适配SCP端口2222
obj-m += jc_mlp_module.o

# 内核源码目录（根据您的实际情况修改）
KERNEL_DIR ?= $(HOME)/autodl-tmp/linux-6.6

# 架构和交叉编译工具链
ARCH ?= riscv
CROSS_COMPILE ?= riscv64-unknown-linux-gnu-

# SCP传输配置（根据您的设置修改）
SCP_PORT ?= 2222
SCP_USER ?= ubuntu
SCP_HOST ?= localhost
REMOTE_DIR ?= /home/$(SCP_USER)/modules

# 默认编译目标
all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

# 清理
clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) clean

# SCP传输模块（端口2222）
scp-transfer: all
	@echo "通过SCP传输模块到 $(SCP_USER)@$(SCP_HOST):$(REMOTE_DIR)/ (端口:$(SCP_PORT))"
	scp -P $(SCP_PORT) jc_mlp_module.ko $(SCP_USER)@$(SCP_HOST):$(REMOTE_DIR)/
	@echo "✓ 传输完成"

# 生成远程测试脚本
deploy-test-script: scp-transfer
	@echo "部署测试脚本到QEMU Ubuntu..."
	scp -P $(SCP_PORT) scripts/test_module.sh $(SCP_USER)@$(SCP_HOST):$(REMOTE_DIR)/
	ssh -p $(SCP_PORT) $(SCP_USER)@$(SCP_HOST) "chmod +x $(REMOTE_DIR)/test_module.sh"
	@echo "✓ 测试脚本部署完成"

# 一键编译、传输并远程测试
remote-test: deploy-test-script
	@echo "在QEMU Ubuntu中执行测试..."
	ssh -p $(SCP_PORT) $(SCP_USER)@$(SCP_HOST) "cd $(REMOTE_DIR) && sudo ./test_module.sh"

.PHONY: all clean scp-transfer deploy-test-script remote-test