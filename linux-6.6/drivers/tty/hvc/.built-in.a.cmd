savedcmd_drivers/tty/hvc/built-in.a := rm -f drivers/tty/hvc/built-in.a;  printf "drivers/tty/hvc/%s " hvc_console.o | xargs riscv64-unknown-linux-gnu-ar cDPrST drivers/tty/hvc/built-in.a
