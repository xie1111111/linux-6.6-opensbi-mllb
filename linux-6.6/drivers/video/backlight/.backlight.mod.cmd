savedcmd_drivers/video/backlight/backlight.mod := printf '%s\n'   backlight.o | awk '!x[$$0]++ { print("drivers/video/backlight/"$$0) }' > drivers/video/backlight/backlight.mod
