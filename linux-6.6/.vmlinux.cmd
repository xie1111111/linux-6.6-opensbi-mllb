savedcmd_vmlinux := scripts/link-vmlinux.sh "riscv64-unknown-linux-gnu-ld" "-melf64lriscv -z noexecstack --no-warn-rwx-segments" "-z norelro --build-id=sha1 --orphan-handling=warn";  make -f ./arch/riscv/Makefile.postlink vmlinux

source_vmlinux := scripts/link-vmlinux.sh

deps_vmlinux := \
    $(wildcard include/config/LTO_CLANG) \
    $(wildcard include/config/X86_KERNEL_IBT) \
    $(wildcard include/config/MODULES) \
    $(wildcard include/config/VMLINUX_MAP) \
    $(wildcard include/config/KALLSYMS_ALL) \
    $(wildcard include/config/KALLSYMS_ABSOLUTE_PERCPU) \
    $(wildcard include/config/KALLSYMS_BASE_RELATIVE) \
    $(wildcard include/config/SHELL) \
    $(wildcard include/config/DEBUG_INFO_BTF) \
    $(wildcard include/config/KALLSYMS) \
    $(wildcard include/config/BPF) \
    $(wildcard include/config/BUILDTIME_TABLE_SORT) \

vmlinux: $(deps_vmlinux)

$(deps_vmlinux):
