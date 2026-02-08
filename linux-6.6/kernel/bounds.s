	.file	"bounds.c"
	.option nopic
# GNU C11 (g1b306039ac4) version 15.1.0 (riscv64-unknown-linux-gnu)
#	compiled by GNU C version 11.3.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version none
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mabi=lp64 -mno-save-restore -mcmodel=medany -mno-riscv-attribute -mstrict-align -misa-spec=20191213 -mtls-dialect=trad -march=rv64imac_zicsr_zifencei_zihintpause_zmmul_zaamo_zalrsc_zca -O2 -std=gnu11 -fshort-wchar -funsigned-char -fno-common -fno-PIE -fno-strict-aliasing -fno-asynchronous-unwind-tables -fno-unwind-tables -fno-delete-null-pointer-checks -fno-allow-store-data-races -fstack-protector-strong -fno-omit-frame-pointer -fno-optimize-sibling-calls -ftrivial-auto-var-init=zero -fno-stack-clash-protection -fstrict-flex-arrays=3 -fno-strict-overflow -fstack-check=no -fconserve-stack
	.text
	.section	.text.startup,"ax",@progbits
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-16	#,,
	sd	s0,0(sp)	#,
	sd	ra,8(sp)	#,
	addi	s0,sp,16	#,,
# kernel/bounds.c:19: 	DEFINE(NR_PAGEFLAGS, __NR_PAGEFLAGS);
#APP
# 19 "kernel/bounds.c" 1
	
.ascii "->NR_PAGEFLAGS 22 __NR_PAGEFLAGS"	#
# 0 "" 2
# kernel/bounds.c:20: 	DEFINE(MAX_NR_ZONES, __MAX_NR_ZONES);
# 20 "kernel/bounds.c" 1
	
.ascii "->MAX_NR_ZONES 3 __MAX_NR_ZONES"	#
# 0 "" 2
# kernel/bounds.c:22: 	DEFINE(NR_CPUS_BITS, ilog2(CONFIG_NR_CPUS));
# 22 "kernel/bounds.c" 1
	
.ascii "->NR_CPUS_BITS 6 ilog2(CONFIG_NR_CPUS)"	#
# 0 "" 2
# kernel/bounds.c:24: 	DEFINE(SPINLOCK_SIZE, sizeof(spinlock_t));
# 24 "kernel/bounds.c" 1
	
.ascii "->SPINLOCK_SIZE 24 sizeof(spinlock_t)"	#
# 0 "" 2
# kernel/bounds.c:29: 	DEFINE(LRU_GEN_WIDTH, 0);
# 29 "kernel/bounds.c" 1
	
.ascii "->LRU_GEN_WIDTH 0 0"	#
# 0 "" 2
# kernel/bounds.c:30: 	DEFINE(__LRU_REFS_WIDTH, 0);
# 30 "kernel/bounds.c" 1
	
.ascii "->__LRU_REFS_WIDTH 0 0"	#
# 0 "" 2
# kernel/bounds.c:35: }
#NO_APP
	ld	ra,8(sp)		#,
	ld	s0,0(sp)		#,
	li	a0,0		#,
	addi	sp,sp,16	#,,
	jr	ra		#
	.size	main, .-main
	.ident	"GCC: (g1b306039ac4) 15.1.0"
	.section	.note.GNU-stack,"",@progbits
