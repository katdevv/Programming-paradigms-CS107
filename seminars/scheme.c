#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "scheme.h"

char *ConcatStrings(const char *s1,const char *s2) {
  int len = strlen(s1) + strlen(s2);

  char* new = malloc(len + 1);
  strcpy(new, s1);
  strcat(new, s2); // adds (concatenates) one string to the end of another

  free(s1);
  free(s2);
  return new;
}

// This function is a recursive reducer over a custom, tagged data structure.
// Its job is to walk a heterogeneous list/tree and return one C string
// that is the concatenation of every string it finds, ignoring integers and Nil.
char* ConcatAll(nodeType *list){
  nodeType type = *list;
  if(type == Nil || type == Integer){
  return strdup("");
  }

  if(type == String){
    char* s = strdup((char*)(list + 1));
    return s;
  }

  // list
  nodeType* elem = *(nodeType**)(list + 1);
  nodeType* nextElem = *(nodeType **)((char *)list + sizeof(nodeType) + sizeof(void *));

  char *elemStr = ConcatAll(elem);
  char *nextElemStr = ConcatAll(nextElem);

  return ConcatStrings(elemStr, nextElemStr);
}

int main(int argc, char **argv) {
  printf("sizeof nodetype = %d\n", sizeof(nodeType));
  nodeType *stringNodes[32] = {};
  nodeType *intNodes   [32] = {};
  nodeType *listNodes  [32] = {};
  nodeType  nilNode = Nil;

  for (int i = 0; i < 32; i++) {
    // some_string is a stack buffer cleared to zeros.
    char some_string[32] = {};

    // Fills it with "test0" … "test31" (e.g., test7).
    sprintf(some_string, "test%d", i);

    nodeType *ptr = malloc(sizeof(nodeType) + strlen(some_string) + 1);

    *ptr = String;

    strcpy((char *)(ptr + 1), some_string);
    stringNodes[i] = ptr;
  }

  for (int i = 0; i < 32; i++) {
    nodeType *ptr = malloc(sizeof(nodeType) + sizeof(int));
    *ptr = Integer;
    memcpy((char*)(ptr + 1), &i, sizeof(int));
    intNodes[i] = ptr;
  }
  for (int i = 0; i < 32; i++) {
    nodeType *ptr = malloc(sizeof(nodeType) + 2*sizeof(void*));
    *ptr = List;

    ((nodeType**)(ptr+1))[0] = &nilNode;
    ((nodeType **) (ptr + 1))[1] = &nilNode;

    listNodes[i] = ptr;
  }
  for (int i = 0; i < 31; i++) {
    ((nodeType**)(listNodes[i] + 1))[1] = listNodes[i + 1];

    if ( i % 2 == 0) {
      ((nodeType **) (listNodes[i] + 1))[0] = stringNodes[i];
    } else {
      ((nodeType **) (listNodes[i] + 1))[0] = intNodes[i];
    }
  }
  printf("%s\n", ConcatAll(listNodes[0]));
}