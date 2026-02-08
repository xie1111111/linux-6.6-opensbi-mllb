savedcmd_fs/devpts/built-in.a := rm -f fs/devpts/built-in.a;  printf "fs/devpts/%s " inode.o | xargs riscv64-unknown-linux-gnu-ar cDPrST fs/devpts/built-in.a
