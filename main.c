#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void StrFree(void* addr){
  free(*(char**)addr); // “Free the memory that the char* points to (the actual string)
}

int main() {
  Stack s;
  StackInit(&s, sizeof(char*), NULL);
  char* a = strdup("freeuni");
  char* b = strdup("agruni");
  char* c = strdup("abcd");
  StackPush(&s, &a);
  StackPush(&s, &b);
  StackPush(&s, &c);
  char* x;
  StackPop(&s, &x);
  printf("%s\n", x);
  free(x);
  StackDestroy(&s);
  return 0;
}