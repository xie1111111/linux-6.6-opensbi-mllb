savedcmd_drivers/hwmon/built-in.a := rm -f drivers/hwmon/built-in.a;  printf "drivers/hwmon/%s " hwmon.o | xargs riscv64-unknown-linux-gnu-ar cDPrST drivers/hwmon/built-in.a
