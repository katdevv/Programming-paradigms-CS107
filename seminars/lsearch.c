#include <stdio.h>
#include <string.h>

/*
int lsearchInt(int* a, int num_elems, int v){
  for(int i = 0; i < num_elems; i++){
    if(a[i] == v){ // *(a + i)
      return i;
    }
  }
  return -1;
}
*/

// memcmp - memory compare - compares number of bytes

int lsearchGeneral(void*a, int num_elems, void* v, int elem_size){
  for(int i = 0; i < num_elems; i++){
    void* p = (char*)a + i * elem_size;
    if(memcmp(p, v, elem_size) == 0) return i;
  }
  return -1;
}


typedef int(*CmpFn)(void*, void*);
/*
CmpFn is now a type.
Any variable of type CmpFn must be a pointer to a function that:
returns an int
takes (void*, void*) arguments.
Think of it like a blueprint:
"CmpFn = pointer to comparator function with this shape."
*/

// this one matches the bluepriny
int IntCmp(void* a, void* b){
  return *(int*)a - *(int*)b;
}

int StrCmp(void* a, void* b){
  // Treat this void* as a pointer to char*so
  char* s = *(char**)a;
  char* t = *(char**)b;
  return strcmp(s, t);
}

int lsearch(void*a, int num_elems, void* v, int elem_size, CmpFn cmp){
  for(int i = 0; i < num_elems; i++){
    void* p = (char*)a + i * elem_size;
    if(cmp(p, v) == 0) return i;
  }
  return -1;
}

int main(){
  int a[5] = {1,2,3,4,5};
  int k = 10;
  // int pos = lsearchGeneral(a, 5, &k, sizeof(int));
  // printf("%d\n", pos);

  char* s[3] = {
    strdup("freeuni"), // allocates heap memory, copies "abcd", returns pointer
    strdup("agruni"), // string dublicate
    strdup("abcd"),
  };
  char *r = "agruni";
  printf("%d\n", lsearch(s, 3, &r, sizeof(char*), StrCmp));
}