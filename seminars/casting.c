#include <stdio.h>

int main() {
  // 00000000 00000000 10010000 00010001
  int i = 17+ (1 << 15) + (1 << 12);

  // 10010000 00010001
  short s = (short) i;
  printf("int: %d\n, short: %d\n\n", i, s);

  unsigned short u = (unsigned short) i;
  printf("int: %d\n, uns short: %d\n\n", i, u);

  // float - 000010000001000100
  // int   - 000000000000000010
  float f = 2.4;
  int fi = (int) f;
  printf("float: %f\n int: %d\n\n", f, fi);

  float *f_pointer = &f;
  int fi_cast = *(int *)f_pointer;

  printf("int fi_cast = %d\n", fi_cast);

}