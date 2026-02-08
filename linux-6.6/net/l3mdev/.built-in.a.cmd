savedcmd_net/l3mdev/built-in.a := rm -f net/l3mdev/built-in.a;  printf "net/l3mdev/%s " l3mdev.o | xargs riscv64-unknown-linux-gnu-ar cDPrST net/l3mdev/built-in.a
