CROSS_COMPILE := riscv64-unknown-linux-gnu-
CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
LD := $(CROSS_COMPILE)ld
AR := $(CROSS_COMPILE)ar
NM := $(CROSS_COMPILE)nm
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump
READELF := $(CROSS_COMPILE)readelf
OBJSIZE := $(CROSS_COMPILE)size
STRIP := $(CROSS_COMPILE)strip
LTO := thin

# ASFLAGS = -march=rv64imac -mabi=lp64 -mcmodel=medany
# ARCH_FLAGS = -march=rv64imac -mabi=lp64 -mcmodel=medany

# 设置交叉编译工具链
export CLANG_TRIPLE := riscv64-unknown-linux-gnu
export ARCH := riscv64
export SUBARCH := riscv64
export HEADER_ARCH := riscv64
export TOOL_ARGS := ARCH=$(ARCH) SUBARCH=$(SUBARCH) HEADER_ARCH=$(HEADER_ARCH) CC=$(CC) CXX=$(CXX) LD=$(LD) AR=$(AR) NM=$(NM) OBJCOPY=$(OBJCOPY) OBJDUMP=$(OBJDUMP) READELF=$(READELF) OBJSIZE=$(OBJSIZE) STRIP=$(STRIP) LLVM=1 LLVM_IAS=1

SBI_PATH := $(OPENSBI_HOME)
LIBSBI_PATH := $(SBI_PATH)/build/lib/libsbi.a
LIBSBIPAT_PATH := $(SBI_PATH)/build/platform/generic/lib/libplatsbi.a
CFLAGS += -I$(SBI_PATH)/include
# LDFLAGS += $(LIBSBI_PATH)
CFLAGS += -mabi=lp64d -march=rv64gcv_zvl256b_zvfh_zvfhmin
# LDFLAGS += -mabi=elf64lriscv_lp64
CFLAGS+=-mcmodel=medany
CFLAGS+=-fno-pic
CFLAGS+=-fno-common
CFLAGS+=-mno-relax
CFLAGS+=-nostdlib -ffreestanding
CFLAGS+= -DPREALLOCATE=1
# CFLAGS+=--target=riscv64-unknown-linux-gnu -march=rv64ima -mabi=lp64
# CFLAGS+=--gcc-toolchain=/opt/riscv --sysroot=/opt/riscv/sysroot/
LDFLAGS+=-z max-page-size=4096 -nostdlib -T src/linker.ld

BUILD_DIR := ./build

$(shell mkdir -p $(BUILD_DIR))

ENTRY_OBJ := $(BUILD_DIR)/entry.o
MAIN_OBJ := $(BUILD_DIR)/main.o
KERNEL_ELF := $(BUILD_DIR)/kernel.elf
KERNEL_BIN := $(BUILD_DIR)/kernel.bin

all: $(KERNEL_BIN) $(KERNEL_ELF).S

$(ENTRY_OBJ): src/entry.s
	$(CC) $(CFLAGS) -c $< -o $@

$(MAIN_OBJ): src/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL_ELF): $(ENTRY_OBJ) $(MAIN_OBJ)
	$(LD) $(LDFLAGS) $^ -o $@ $(LIBSBI_PATH)
# $(LIBSBI_PATH) $(LIBSBIPAT_PATH)
$(KERNEL_ELF).S: $(KERNEL_ELF)
	$(OBJDUMP) -d $^ > $@

$(KERNEL_BIN): $(KERNEL_ELF)
	$(OBJCOPY) -O binary $< $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
