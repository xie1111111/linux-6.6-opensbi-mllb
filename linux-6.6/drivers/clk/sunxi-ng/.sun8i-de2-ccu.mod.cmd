savedcmd_drivers/clk/sunxi-ng/sun8i-de2-ccu.mod := printf '%s\n'   ccu-sun8i-de2.o | awk '!x[$$0]++ { print("drivers/clk/sunxi-ng/"$$0) }' > drivers/clk/sunxi-ng/sun8i-de2-ccu.mod
