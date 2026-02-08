savedcmd_scripts/module.lds := riscv64-unknown-linux-gnu-gcc -E -Wp,-MMD,scripts/.module.lds.d -nostdinc -I./arch/riscv/include -I./arch/riscv/include/generated  -I./include -I./arch/riscv/include/uapi -I./arch/riscv/include/generated/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/compiler-version.h -include ./include/linux/kconfig.h -D__KERNEL__ -fmacro-prefix-map=./=   -P -Uriscv -D__ASSEMBLY__ -DLINKER_SCRIPT -o scripts/module.lds scripts/module.lds.S

source_scripts/module.lds := scripts/module.lds.S

deps_scripts/module.lds := \
    $(wildcard include/config/UNWIND_TABLES) \
    $(wildcard include/config/ARCH_USES_CFI_TRAPS) \
    $(wildcard include/config/LTO_CLANG) \
  include/linux/compiler-version.h \
    $(wildcard include/config/CC_VERSION_TEXT) \
  include/linux/kconfig.h \
    $(wildcard include/config/CPU_BIG_ENDIAN) \
    $(wildcard include/config/BOOGER) \
    $(wildcard include/config/FOO) \
  arch/riscv/include/asm/module.lds.h \
    $(wildcard include/config/MODULE_SECTIONS) \

scripts/module.lds: $(deps_scripts/module.lds)

$(deps_scripts/module.lds):
