savedcmd_arch/riscv/kernel/copy-unaligned.o := riscv64-unknown-linux-gnu-gcc -Wp,-MMD,arch/riscv/kernel/.copy-unaligned.o.d -nostdinc -I./arch/riscv/include -I./arch/riscv/include/generated  -I./include -I./arch/riscv/include/uapi -I./arch/riscv/include/generated/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/compiler-version.h -include ./include/linux/kconfig.h -D__KERNEL__ -fmacro-prefix-map=./= -D__ASSEMBLY__ -fno-PIE -mabi=lp64 -march=rv64imafdc_zicsr_zifencei_zihintpause -mno-riscv-attribute -Wa,-mno-arch-attr    -c -o arch/riscv/kernel/copy-unaligned.o arch/riscv/kernel/copy-unaligned.S 

source_arch/riscv/kernel/copy-unaligned.o := arch/riscv/kernel/copy-unaligned.S

deps_arch/riscv/kernel/copy-unaligned.o := \
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

arch/riscv/kernel/copy-unaligned.o: $(deps_arch/riscv/kernel/copy-unaligned.o)

$(deps_arch/riscv/kernel/copy-unaligned.o):
