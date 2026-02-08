# 环境配置 ~/mini_kernel
export CROSS_COMPILE=riscv64-unknown-linux-gnu-
export WORK_SPACE=${HOME}/autodl-tmp/opensbi-mle
export OPENSBI_HOME=$(WORK_SPACE)/opensbi
export OPENSBI_ORG_HOME=$(WORK_SPACE)/opensbi_org
export AM_HOME=$(WORK_SPACE)/abstract-machine
export ISA=riscv64

# 默认目标
.PHONY: demo

demo: build_opensbi build_demo

# 构建 OpenSBI
build_opensbi:
	@echo "Building OpenSBI..."
	cd $(OPENSBI_HOME) && make all PLATFORM=generic PLATFORM_RISCV_XLEN=64 PLATFORM_RISCV_ABI=lp64d PLATFORM_RISCV_ISA=rv64imafdc_zicsr_zifencei_
build_opensbi_org:
	@echo "Building OpenSBI..."
	cd $(OPENSBI_ORG_HOME) && make all PLATFORM=generic PLATFORM_RISCV_XLEN=64 PLATFORM_RISCV_ABI=lp64d PLATFORM_RISCV_ISA=rv64imafdc_zicsr_zifencei_
# 构建并运行 Demo
build_demo:
	@echo "Building and running demo..."
	cd $(WORK_SPACE)/mini-kernel-test/rvv && make ARCH=riscv64-sbiqemu run TEST=matmul
test_kernel:
	make -C mini-kernel-test all
IMAGE :=mini-kernel-test/build/kernel

QEMU_FLAGS += -M virt -m 512M -nographic \
                -bios $(OPENSBI_HOME)/build/platform/generic/firmware/fw_jump.bin \
                -kernel $(IMAGE).elf  \
                -cpu rv64,v=true,vlen=256,vext_spec=v1.0,zvfhmin=on,zvfh=on

run:test_kernel
	@qemu-system-riscv64 $(QEMU_FLAGS)