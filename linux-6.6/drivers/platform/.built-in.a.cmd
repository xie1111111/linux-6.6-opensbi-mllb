savedcmd_drivers/platform/built-in.a := rm -f drivers/platform/built-in.a;  printf "drivers/platform/%s " goldfish/built-in.a | xargs riscv64-unknown-linux-gnu-ar cDPrST drivers/platform/built-in.a
