savedcmd_arch/riscv/boot/Image := riscv64-unknown-linux-gnu-objcopy  -O binary -R .note -R .note.gnu.build-id -R .comment -S vmlinux arch/riscv/boot/Image
