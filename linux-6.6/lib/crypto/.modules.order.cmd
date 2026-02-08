savedcmd_lib/crypto/modules.order := {   cat lib/crypto/mpi/modules.order;   echo lib/crypto/libaes.o;   echo lib/crypto/gf128mul.o;   echo lib/crypto/libsha256.o; :; } > lib/crypto/modules.order
