riscv64-linux-gnu-gcc -ffreestanding -nostdlib -c main.c -o main.o
riscv64-linux-gnu-ld -o kernel.elf -Tlinker.ld entry.o main.o
exit

riscv64-linux-gnu-gcc -ffreestanding -nostdlib -Wl,-Ttext=0x80200000 -O2 main.c -o kernel
echo qemu-system-riscv32 -nographic -M virt -bios none -kernel kernel
riscv64-unknown-elf-strip kernel.elf --strip-all -O binary -o kernel.bin
riscv64-linux-gnu-strip kernel --strip-all -O binary -o kernel.bin

export AM_HOME=/nfs/home/leguochun/mini_kernel/abstract-machine
export ISA=riscv64
export PATH="/nfs/home/leguochun/local/bin:$PATH"
export PATH="/nfs/home/leguochun/jupiter-linux/spacemit-toolchain-linux-glibc-x86_64-v1.0.5/bin:$PATH"
export CROSS_COMPILE=riscv64-unknown-linux-gnu-
