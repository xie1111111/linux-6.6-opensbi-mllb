savedcmd_drivers/spi/built-in.a := rm -f drivers/spi/built-in.a;  printf "drivers/spi/%s " spi.o spi-sifive.o spi-sun6i.o | xargs riscv64-unknown-linux-gnu-ar cDPrST drivers/spi/built-in.a
