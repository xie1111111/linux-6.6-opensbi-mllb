savedcmd_drivers/extcon/built-in.a := rm -f drivers/extcon/built-in.a;  printf "drivers/extcon/%s " extcon.o devres.o | xargs riscv64-unknown-linux-gnu-ar cDPrST drivers/extcon/built-in.a
