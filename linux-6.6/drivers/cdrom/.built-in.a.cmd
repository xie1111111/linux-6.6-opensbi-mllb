savedcmd_drivers/cdrom/built-in.a := rm -f drivers/cdrom/built-in.a;  printf "drivers/cdrom/%s " cdrom.o | xargs riscv64-unknown-linux-gnu-ar cDPrST drivers/cdrom/built-in.a
