savedcmd_lib/crypto/gf128mul.mod := printf '%s\n'   gf128mul.o | awk '!x[$$0]++ { print("lib/crypto/"$$0) }' > lib/crypto/gf128mul.mod
