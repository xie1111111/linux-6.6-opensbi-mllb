savedcmd_arch/riscv/kernel/vdso/note.o := riscv64-unknown-linux-gnu-gcc -Wp,-MMD,arch/riscv/kernel/vdso/.note.o.d -nostdinc -I./arch/riscv/include -I./arch/riscv/include/generated  -I./include -I./arch/riscv/include/uapi -I./arch/riscv/include/generated/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/compiler-version.h -include ./include/linux/kconfig.h -D__KERNEL__ -fmacro-prefix-map=./= -D__ASSEMBLY__ -fno-PIE -mabi=lp64 -march=rv64imafdc_zicsr_zifencei_zihintpause -mno-riscv-attribute -Wa,-mno-arch-attr    -c -o arch/riscv/kernel/vdso/note.o arch/riscv/kernel/vdso/note.S 

source_arch/riscv/kernel/vdso/note.o := arch/riscv/kernel/vdso/note.S

deps_arch/riscv/kernel/vdso/note.o := \
  include/linux/compiler-version.h \
    $(wildcard include/config/CC_VERSION_TEXT) \
  include/linux/kconfig.h \
    $(wildcard include/config/CPU_BIG_ENDIAN) \
    $(wildcard include/config/BOOGER) \
    $(wildcard include/config/FOO) \
  include/linux/elfnote.h \
  include/generated/uapi/linux/version.h \

arch/riscv/kernel/vdso/note.o: $(deps_arch/riscv/kernel/vdso/note.o)

$(deps_arch/riscv/kernel/vdso/note.o):
