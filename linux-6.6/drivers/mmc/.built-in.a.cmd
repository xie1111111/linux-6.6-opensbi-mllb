savedcmd_drivers/mmc/built-in.a := rm -f drivers/mmc/built-in.a;  printf "drivers/mmc/%s " core/built-in.a host/built-in.a | xargs riscv64-unknown-linux-gnu-ar cDPrST drivers/mmc/built-in.a
