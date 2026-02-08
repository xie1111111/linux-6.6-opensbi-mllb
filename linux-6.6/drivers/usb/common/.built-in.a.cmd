savedcmd_drivers/usb/common/built-in.a := rm -f drivers/usb/common/built-in.a;  printf "drivers/usb/common/%s " common.o | xargs riscv64-unknown-linux-gnu-ar cDPrST drivers/usb/common/built-in.a
