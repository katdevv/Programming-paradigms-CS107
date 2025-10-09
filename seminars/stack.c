#include "stack.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define INIT_ALLOC_LEN 4
#define ELEM_ADDR(s, i) (char*)s->base + i *s->elem_size

void StackInit(Stack* s, int elem_size, FreeFn free_fn){
  s->elem_size = elem_size;
  s->base = malloc(elem_size * s->elem_size);
  assert(s->base != NULL); // if malloc returned null, crash
  s->log_len = 0;
  s->alloc_len = INIT_ALLOC_LEN;
  s->free_fn = free_fn;
}

void StackDestroy(Stack* s){
  if(s->free_fn != NULL){
    for(int i = 0; i < s->log_len; i++){
      s->free_fn(ELEM_ADDR(s, i));
    }
  }
  free(s->base);
}

void StackPush(Stack* s, void* v){
  if(s->log_len == s->alloc_len){
    s->alloc_len *= 2;
    s->base = realloc(s->base, s->alloc_len*s->elem_size);
    assert(s->base != NULL);
  }
  void* elemAddr = ELEM_ADDR(s, s->log_len);
  memcpy(elemAddr, v, s->elem_size);
  s->log_len++;
}

void StackPop(Stack* s, void* addr){
  assert(s->log_len > 0);
  s->log_len--;
  void* elemAddr = ELEM_ADDR(s, s->log_len);
  memcpy(addr, elemAddr, s->elem_size);
}

int StackSize(Stack* s){
  return s->log_len;
}

void StrFree(void* addr){
  free(*(char**)addr); // “Free the memory that the char* points to (the actual string)
}


int main(int argc, char **argv) {

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
  */

}