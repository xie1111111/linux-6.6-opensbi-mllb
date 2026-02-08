savedcmd_fs/nls/built-in.a := rm -f fs/nls/built-in.a;  printf "fs/nls/%s " nls_base.o nls_cp437.o | xargs riscv64-unknown-linux-gnu-ar cDPrST fs/nls/built-in.a
