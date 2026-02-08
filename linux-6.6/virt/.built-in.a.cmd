savedcmd_virt/built-in.a := rm -f virt/built-in.a;  printf "virt/%s " lib/built-in.a | xargs riscv64-unknown-linux-gnu-ar cDPrST virt/built-in.a
