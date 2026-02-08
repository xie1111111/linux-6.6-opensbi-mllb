savedcmd_lib/lzo/built-in.a := rm -f lib/lzo/built-in.a;  printf "lib/lzo/%s " lzo1x_decompress_safe.o | xargs riscv64-unknown-linux-gnu-ar cDPrST lib/lzo/built-in.a
