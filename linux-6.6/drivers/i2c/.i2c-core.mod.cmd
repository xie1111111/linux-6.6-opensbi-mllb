savedcmd_drivers/i2c/i2c-core.mod := printf '%s\n'   i2c-core-base.o i2c-core-smbus.o i2c-core-acpi.o i2c-core-of.o | awk '!x[$$0]++ { print("drivers/i2c/"$$0) }' > drivers/i2c/i2c-core.mod
