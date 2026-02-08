AM_SRCS := riscv/sbiqemu/start.S \
           riscv/sbiqemu/trm.c \
           platform/dummy/ioe.c \
           platform/dummy/cte.c \
           platform/dummy/vme.c \
           platform/dummy/mpe.c

CFLAGS    += -fdata-sections -ffunction-sections
LDFLAGS   += -T $(AM_HOME)/scripts/linker.ld \
						 --defsym=_pmem_start=0x80200000 --defsym=_entry_offset=0x0
LDFLAGS   += --gc-sections -e _start
CFLAGS += -DMAINARGS=\"$(mainargs)\"
COMMON_CFLAGS += -mabi=lp64d -march=rv64gcv_zvl256b_zvfh_zvfhmin # overwrite
.PHONY: $(AM_HOME)/am/src/riscv/npc/trm.c

image: $(IMAGE).elf
	@$(OBJDUMP) -d $(IMAGE).elf > $(IMAGE).txt
	@echo + OBJCOPY "->" $(IMAGE_REL).bin
	@$(OBJCOPY) -S --set-section-flags .bss=alloc,contents -O binary $(IMAGE).elf $(IMAGE).bin


.PHONY: build-arg

# LDFLAGS    += -N -Ttext-segment=0x00100000
QEMU_FLAGS += -M virt -m 512M -nographic \
                -bios $(OPENSBI_HOME)/build/platform/generic/firmware/fw_jump.bin \
                -kernel $(IMAGE).elf  \
                -cpu rv64,v=true,vlen=256,vext_spec=v1.0,zvfhmin=on,zvfh=on
# build-arg: image
# 	@( echo -n $(mainargs); ) | dd if=/dev/stdin of=$(IMAGE) bs=512 count=2 seek=1 conv=notrunc status=none

# BOOT_HOME := $(AM_HOME)/am/src/x86/qemu/boot

# image: $(IMAGE).elf
# 	@$(MAKE) -s -C $(BOOT_HOME)
# 	@echo + CREATE "->" $(IMAGE_REL)
# 	@( cat $(BOOT_HOME)/bootblock.o; head -c 1024 /dev/zero; cat $(IMAGE).elf ) > $(IMAGE)
