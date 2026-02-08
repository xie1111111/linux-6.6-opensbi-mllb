savedcmd_drivers/input/keyboard/sun4i-lradc-keys.mod := printf '%s\n'   sun4i-lradc-keys.o | awk '!x[$$0]++ { print("drivers/input/keyboard/"$$0) }' > drivers/input/keyboard/sun4i-lradc-keys.mod
