#include <am.h>
#include <klib-macros.h>

extern char _heap_start;
int main(const char *args);

extern char _pmem_start;
#define PMEM_SIZE (128 * 1024 * 1024)
#define PMEM_END  ((uintptr_t)&_pmem_start + PMEM_SIZE)
#define SERIAL_MMIO 0xa00003f8

Area heap = RANGE(&_heap_start, PMEM_END);
#ifndef MAINARGS
#define MAINARGS ""
#endif
static const char mainargs[] = MAINARGS;

void putch(char ch) {
  char *devices=(char *)SERIAL_MMIO;
  *devices=ch;
}

void halt(int code) {
  asm volatile("mv a0, %0; ebreak" : : "r"(code));
  while (1);//TODO halt 实现
}

void _trm_init() {
  int ret = main(mainargs);
  halt(ret);
}
