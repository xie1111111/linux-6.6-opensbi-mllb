savedcmd_drivers/soc/sunxi/built-in.a := rm -f drivers/soc/sunxi/built-in.a;  printf "drivers/soc/sunxi/%s " sunxi_sram.o | xargs riscv64-unknown-linux-gnu-ar cDPrST drivers/soc/sunxi/built-in.a
