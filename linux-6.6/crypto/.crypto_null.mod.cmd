savedcmd_crypto/crypto_null.mod := printf '%s\n'   crypto_null.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/crypto_null.mod
