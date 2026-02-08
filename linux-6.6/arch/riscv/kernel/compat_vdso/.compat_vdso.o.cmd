savedcmd_arch/riscv/kernel/compat_vdso/compat_vdso.o := riscv64-unknown-linux-gnu-gcc -Wp,-MMD,arch/riscv/kernel/compat_vdso/.compat_vdso.o.d -nostdinc -I./arch/riscv/include -I./arch/riscv/include/generated  -I./include -I./arch/riscv/include/uapi -I./arch/riscv/include/generated/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/compiler-version.h -include ./include/linux/kconfig.h -D__KERNEL__ -fmacro-prefix-map=./= -D__ASSEMBLY__ -fno-PIE -mabi=lp64 -march=rv64imafdc_zicsr_zifencei_zihintpause -mno-riscv-attribute -Wa,-mno-arch-attr    -c -o arch/riscv/kernel/compat_vdso/compat_vdso.o arch/riscv/kernel/compat_vdso/compat_vdso.S 

source_arch/riscv/kernel/compat_vdso/compat_vdso.o := arch/riscv/kernel/compat_vdso/compat_vdso.S

deps_arch/riscv/kernel/compat_vdso/compat_vdso.o := \
  include/linux/compiler-version.h \
    $(wildcard include/config/CC_VERSION_TEXT) \
  include/linux/kconfig.h \
    $(wildcard include/config/CPU_BIG_ENDIAN) \
    $(wildcard include/config/BOOGER) \
    $(wildcard include/config/FOO) \
  arch/riscv/kernel/compat_vdso/../vdso/vdso.S \
  include/linux/init.h \
    $(wildcard include/config/HAVE_ARCH_PREL32_RELOCATIONS) \
    $(wildcard include/config/STRICT_KERNEL_RWX) \
    $(wildcard include/config/STRICT_MODULE_RWX) \
    $(wildcard include/config/LTO_CLANG) \
  include/linux/build_bug.h \
  include/linux/compiler.h \
    $(wildcard include/config/TRACE_BRANCH_PROFILING) \
    $(wildcard include/config/PROFILE_ALL_BRANCHES) \
    $(wildcard include/config/OBJTOOL) \
  include/linux/compiler_types.h \
    $(wildcard include/config/DEBUG_INFO_BTF) \
    $(wildcard include/config/PAHOLE_HAS_BTF_TAG) \
    $(wildcard include/config/FUNCTION_ALIGNMENT) \
    $(wildcard include/config/CC_IS_GCC) \
    $(wildcard include/config/X86_64) \
    $(wildcard include/config/ARM64) \
    $(wildcard include/config/HAVE_ARCH_COMPILER_H) \
    $(wildcard include/config/CC_HAS_ASM_INLINE) \
  arch/riscv/include/generated/asm/rwonce.h \
  include/asm-generic/rwonce.h \
  include/linux/stringify.h \
  include/linux/types.h \
    $(wildcard include/config/HAVE_UID16) \
    $(wildcard include/config/UID16) \
    $(wildcard include/config/ARCH_DMA_ADDR_T_64BIT) \
    $(wildcard include/config/PHYS_ADDR_T_64BIT) \
    $(wildcard include/config/64BIT) \
    $(wildcard include/config/ARCH_32BIT_USTAT_F_TINODE) \
  include/uapi/linux/types.h \
  arch/riscv/include/generated/uapi/asm/types.h \
  include/uapi/asm-generic/types.h \
  include/asm-generic/int-ll64.h \
  include/uapi/asm-generic/int-ll64.h \
  arch/riscv/include/uapi/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/uapi/asm-generic/bitsperlong.h \
  include/linux/linkage.h \
    $(wildcard include/config/ARCH_USE_SYM_ANNOTATIONS) \
  include/linux/export.h \
    $(wildcard include/config/MODVERSIONS) \
  arch/riscv/include/asm/linkage.h \
  arch/riscv/include/asm/page.h \
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

arch/riscv/kernel/compat_vdso/compat_vdso.o: $(deps_arch/riscv/kernel/compat_vdso/compat_vdso.o)

$(deps_arch/riscv/kernel/compat_vdso/compat_vdso.o):
