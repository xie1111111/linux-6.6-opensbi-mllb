#include <am.h>
#include <klib.h>
#include <klib-macros.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
static unsigned long int next = 1;

int rand(void) {
  // RAND_MAX assumed to be 32767
  next = next * 1103515245 + 12345;
  return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed) {
  next = seed;
}

int abs(int x) {
  return (x < 0 ? -x : x);
}

int atoi(const char* nptr) {
  int x = 0;
  while (*nptr == ' ') { nptr ++; }
  while (*nptr >= '0' && *nptr <= '9') {
    x = x * 10 + *nptr - '0';
    nptr ++;
  }
  return x;
}
static char *last_malloc_addr=NULL;

void *malloc(size_t size) {
  char *ret=NULL;

  if(size==0){
    return NULL;
  }
  if(last_malloc_addr==NULL){
    // 初始化
    last_malloc_addr=(void *)ROUNDUP(heap.start,8);// 8位上对齐的地址;
  }
  ret=last_malloc_addr;
  last_malloc_addr+=(size_t)ROUNDUP(size,8);
  if(last_malloc_addr>=(char *)heap.end){
    last_malloc_addr=ret;
    return NULL;
  }
  return ret;
}

void free(void *ptr) {
}

#endif
