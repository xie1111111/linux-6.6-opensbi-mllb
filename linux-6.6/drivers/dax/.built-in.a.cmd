savedcmd_drivers/dax/built-in.a := rm -f drivers/dax/built-in.a;  printf "drivers/dax/%s " super.o bus.o hmem/built-in.a | xargs riscv64-unknown-linux-gnu-ar cDPrST drivers/dax/built-in.a
