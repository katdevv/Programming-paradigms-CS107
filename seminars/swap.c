#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(void* a, void*b, int elem_size){
  void* tmp = malloc(elem_size);
  memcpy(tmp, a, elem_size);
  memcpy(a, b, elem_size);
  memcpy(b, tmp, elem_size);
  free(tmp);
}

int main(int argc, char** argv) {
  int x = 5;
  int y = 7;
  printf("%d %d\n", x, y);
  swap(&x, &y, sizeof(int));
  // swap(x, y);
  printf("%d %d\n", x, y);
  double q = 1.3;
  double w = 5.7;
  swap(&q, &w, sizeof(double));
  printf("%f %f\n", q, w);
  return 0;
}