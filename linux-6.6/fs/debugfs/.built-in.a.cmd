savedcmd_fs/debugfs/built-in.a := rm -f fs/debugfs/built-in.a;  printf "fs/debugfs/%s " inode.o file.o | xargs riscv64-unknown-linux-gnu-ar cDPrST fs/debugfs/built-in.a
