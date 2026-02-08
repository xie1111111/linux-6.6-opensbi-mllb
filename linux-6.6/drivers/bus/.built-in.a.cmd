savedcmd_drivers/bus/built-in.a := rm -f drivers/bus/built-in.a;  printf "drivers/bus/%s " simple-pm-bus.o mhi/built-in.a | xargs riscv64-unknown-linux-gnu-ar cDPrST drivers/bus/built-in.a
