savedcmd_drivers/acpi/riscv/built-in.a := rm -f drivers/acpi/riscv/built-in.a;  printf "drivers/acpi/riscv/%s " rhct.o | xargs riscv64-unknown-linux-gnu-ar cDPrST drivers/acpi/riscv/built-in.a
