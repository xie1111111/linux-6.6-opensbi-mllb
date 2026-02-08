savedcmd_net/bpf/built-in.a := rm -f net/bpf/built-in.a;  printf "net/bpf/%s " test_run.o | xargs riscv64-unknown-linux-gnu-ar cDPrST net/bpf/built-in.a
