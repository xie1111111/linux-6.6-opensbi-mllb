savedcmd_arch/riscv/kernel/vdso/vdso.lds := riscv64-unknown-linux-gnu-gcc -E -Wp,-MMD,arch/riscv/kernel/vdso/.vdso.lds.d -nostdinc -I./arch/riscv/include -I./arch/riscv/include/generated  -I./include -I./arch/riscv/include/uapi -I./arch/riscv/include/generated/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/compiler-version.h -include ./include/linux/kconfig.h -D__KERNEL__ -fmacro-prefix-map=./=  -P -C -Uriscv -DHAS_VGETTIMEOFDAY -P -Uriscv -D__ASSEMBLY__ -DLINKER_SCRIPT -o arch/riscv/kernel/vdso/vdso.lds arch/riscv/kernel/vdso/vdso.lds.S

source_arch/riscv/kernel/vdso/vdso.lds := arch/riscv/kernel/vdso/vdso.lds.S

deps_arch/riscv/kernel/vdso/vdso.lds := \
    $(wildcard include/config/TIME_NS) \
  include/linux/compiler-version.h \
    $(wildcard include/config/CC_VERSION_TEXT) \
  include/linux/kconfig.h \
    $(wildcard include/config/CPU_BIG_ENDIAN) \
    $(wildcard include/config/BOOGER) \
    $(wildcard include/config/FOO) \
  arch/riscv/include/asm/page.h \
    $(wildcard include/config/64BIT) \
    $(wildcard include/config/MMU) \
    $(wildcard include/config/PAGE_OFFSET) \
    $(wildcard include/config/RISCV_ISA_ZICBOZ) \
    $(wildcard include/config/XIP_KERNEL) \
    $(wildcard include/config/DEBUG_VIRTUAL) \
  include/linux/pfn.h \
  include/linux/const.h \
  include/vdso/const.h \
  include/uapi/linux/const.h \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/FLATMEM) \
    $(wildcard include/config/SPARSEMEM_VMEMMAP) \
    $(wildcard include/config/SPARSEMEM) \
  include/asm-generic/getorder.h \
  arch/riscv/include/asm/vdso.h \
    $(wildcard include/config/COMPAT) \

arch/riscv/kernel/vdso/vdso.lds: $(deps_arch/riscv/kernel/vdso/vdso.lds)

$(deps_arch/riscv/kernel/vdso/vdso.lds):
