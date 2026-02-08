savedcmd_drivers/usb/phy/built-in.a := rm -f drivers/usb/phy/built-in.a;  printf "drivers/usb/phy/%s " phy.o of.o | xargs riscv64-unknown-linux-gnu-ar cDPrST drivers/usb/phy/built-in.a
