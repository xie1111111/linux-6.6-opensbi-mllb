include $(AM_HOME)/scripts/isa/riscv.mk
include $(AM_HOME)/scripts/platform/sbiqemu.mk

# AM_SRCS += riscv/nemu/start.S \
#            riscv/nemu/cte.c \
#            riscv/nemu/trap.S \
#            riscv/nemu/vme.c

run: image
	@qemu-system-riscv64 $(QEMU_FLAGS)
