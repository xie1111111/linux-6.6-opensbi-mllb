savedcmd_lib/raid6/raid6_pq.mod := printf '%s\n'   algos.o recov.o tables.o int1.o int2.o int4.o int8.o int16.o int32.o | awk '!x[$$0]++ { print("lib/raid6/"$$0) }' > lib/raid6/raid6_pq.mod
