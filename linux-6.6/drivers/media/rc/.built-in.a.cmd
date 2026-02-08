savedcmd_drivers/media/rc/built-in.a := rm -f drivers/media/rc/built-in.a;  printf "drivers/media/rc/%s " keymaps/built-in.a | xargs riscv64-unknown-linux-gnu-ar cDPrST drivers/media/rc/built-in.a
