#include <am.h>
#include "sbiqemu.h"

extern char _heap_start;
int main(const char *args);

extern char _pmem_start;
// #define PMEM_SIZE (128 * 1024 * 1024)
// #define PMEM_END  ((uintptr_t)&_pmem_start + PMEM_SIZE)
// #define SERIAL_MMIO 0xa00003f8

Area heap = RANGE(&_heap_start, PMEM_END);
#ifndef MAINARGS
#define MAINARGS ""
#endif
static const char mainargs[] = MAINARGS;
// Area heap = RANGE(&_heap_start, PMEM_END);

void putch(char ch) {
  // outb(SERIAL_PORT, ch);//puts速度更快

  register unsigned long a0 asm("a0") = (unsigned long)(ch);
  register unsigned long a1 asm("a1") = (unsigned long)(0);
  register unsigned long a2 asm("a2") = (unsigned long)(0);
  register unsigned long a7 asm("a7") = (unsigned long)(1);
  asm volatile("ecall" : "+r"(a0) : "r"(a1), "r"(a2), "r"(a7) : "memory");
  // return a0; // return void;

}

void halt(int code) {
  // asm volatile("mv a0, %0; ebreak" : : "r"(code));
  while (1);//TODO halt 实现
}

void _trm_init() {
  int ret = main(mainargs);
  halt(ret);
}
