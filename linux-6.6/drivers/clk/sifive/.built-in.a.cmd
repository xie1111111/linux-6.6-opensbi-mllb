savedcmd_drivers/clk/sifive/built-in.a := rm -f drivers/clk/sifive/built-in.a;  printf "drivers/clk/sifive/%s " sifive-prci.o | xargs riscv64-unknown-linux-gnu-ar cDPrST drivers/clk/sifive/built-in.a
