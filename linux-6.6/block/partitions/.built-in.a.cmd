savedcmd_block/partitions/built-in.a := rm -f block/partitions/built-in.a;  printf "block/partitions/%s " core.o msdos.o efi.o | xargs riscv64-unknown-linux-gnu-ar cDPrST block/partitions/built-in.a
