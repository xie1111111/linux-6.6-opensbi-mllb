savedcmd_drivers/nvme/built-in.a := rm -f drivers/nvme/built-in.a;  printf "drivers/nvme/%s " host/built-in.a target/built-in.a | xargs riscv64-unknown-linux-gnu-ar cDPrST drivers/nvme/built-in.a
