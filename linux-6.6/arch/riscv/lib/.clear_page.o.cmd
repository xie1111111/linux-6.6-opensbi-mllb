savedcmd_arch/riscv/lib/clear_page.o := riscv64-unknown-linux-gnu-gcc -Wp,-MMD,arch/riscv/lib/.clear_page.o.d -nostdinc -I./arch/riscv/include -I./arch/riscv/include/generated  -I./include -I./arch/riscv/include/uapi -I./arch/riscv/include/generated/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/compiler-version.h -include ./include/linux/kconfig.h -D__KERNEL__ -fmacro-prefix-map=./= -D__ASSEMBLY__ -fno-PIE -mabi=lp64 -march=rv64imafdc_zicsr_zifencei_zihintpause -mno-riscv-attribute -Wa,-mno-arch-attr    -c -o arch/riscv/lib/clear_page.o arch/riscv/lib/clear_page.S 

source_arch/riscv/lib/clear_page.o := arch/riscv/lib/clear_page.S

deps_arch/riscv/lib/clear_page.o := \
    $(wildcard include/config/RISCV_ISA_ZICBOZ) \
  include/linux/compiler-version.h \
    $(wildcard include/config/CC_VERSION_TEXT) \
  include/linux/kconfig.h \
    $(wildcard include/config/CPU_BIG_ENDIAN) \
    $(wildcard include/config/BOOGER) \
    $(wildcard include/config/FOO) \
  include/linux/linkage.h \
    $(wildcard include/config/FUNCTION_ALIGNMENT) \
    $(wildcard include/config/ARCH_USE_SYM_ANNOTATIONS) \
  include/linux/compiler_types.h \
    $(wildcard include/config/DEBUG_INFO_BTF) \
    $(wildcard include/config/PAHOLE_HAS_BTF_TAG) \
    $(wildcard include/config/CC_IS_GCC) \
    $(wildcard include/config/X86_64) \
    $(wildcard include/config/ARM64) \
    $(wildcard include/config/HAVE_ARCH_COMPILER_H) \
    $(wildcard include/config/CC_HAS_ASM_INLINE) \
  include/linux/stringify.h \
  include/linux/export.h \
    $(wildcard include/config/MODVERSIONS) \
    $(wildcard include/config/64BIT) \
  include/linux/compiler.h \
    $(wildcard include/config/TRACE_BRANCH_PROFILING) \
    $(wildcard include/config/PROFILE_ALL_BRANCHES) \
    $(wildcard include/config/OBJTOOL) \
  arch/riscv/include/generated/asm/rwonce.h \
  include/asm-generic/rwonce.h \
  arch/riscv/include/asm/linkage.h \
  arch/riscv/include/asm/asm.h \
  arch/riscv/include/asm/asm-offsets.h \
  include/generated/asm-offsets.h \
  arch/riscv/include/asm/alternative-macros.h \
    $(wildcard include/config/RISCV_ALTERNATIVE) \
    $(wildcard include/config/k) \
    $(wildcard include/config/k_1) \
    $(wildcard include/config/k_2) \
  include/asm-generic/export.h \
  arch/riscv/include/asm/hwcap.h \
    $(wildcard include/config/RISCV_M_MODE) \
  arch/riscv/include/generated/uapi/asm/errno.h \
  include/uapi/asm-generic/errno.h \
  include/uapi/asm-generic/errno-base.h \
  include/linux/bits.h \
  include/linux/const.h \
  include/vdso/const.h \
  include/uapi/linux/const.h \
  include/vdso/bits.h \
  arch/riscv/include/uapi/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/uapi/asm-generic/bitsperlong.h \
  arch/riscv/include/uapi/asm/hwcap.h \
  arch/riscv/include/asm/insn-def.h \
    $(wildcard include/config/AS_HAS_INSN) \
  arch/riscv/include/asm/page.h \
    $(wildcard include/config/MMU) \
    $(wildcard include/config/PAGE_OFFSET) \
    $(wildcard include/config/XIP_KERNEL) \
    $(wildcard include/config/DEBUG_VIRTUAL) \
  include/linux/pfn.h \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/FLATMEM) \
    $(wildcard include/config/SPARSEMEM_VMEMMAP) \
    $(wildcard include/config/SPARSEMEM) \
  include/asm-generic/getorder.h \

arch/riscv/lib/clear_page.o: $(deps_arch/riscv/lib/clear_page.o)

$(deps_arch/riscv/lib/clear_page.o):
