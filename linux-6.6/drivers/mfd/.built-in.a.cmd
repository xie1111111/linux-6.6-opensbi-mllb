savedcmd_drivers/mfd/built-in.a := rm -f drivers/mfd/built-in.a;  printf "drivers/mfd/%s " syscon.o | xargs riscv64-unknown-linux-gnu-ar cDPrST drivers/mfd/built-in.a
