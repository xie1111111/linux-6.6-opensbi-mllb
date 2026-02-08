#include <am.h>
#include <klib-macros.h>
#include <stdio.h>

int main(const char *args) {
  const char *fmt =
    "Hello, AbstractMachine!\n"
    "mainargs = '%'.\n";

  for (const char *p = fmt; *p; p++) {
    (*p == '%') ? putstr(args) : putch(*p);
  }
  float x=3.1415926;
  // int y=671;
  printf("test%06.8f %d\n", x, 19);
  return 0;
}
