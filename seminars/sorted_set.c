#include "sorted_set.h"

static const int kInitialCapacity = 4;

void SetNew(sortedset *set, int elemSize, int (*cmpfn)(const void *, const void *)) {
  set->base = malloc(KinitialCapacity * (elemSize + 2 *sizeof(int) + sizeof(int));
  *(int *)set->base = -1;
  set->elemSize = elemSize;
  set->allocLen = kInitialCapacity;
  set->logLen = 0;
  set->cmpfn = cmpfn;
}

int *findElem(sortedset *set, const void *elemPtr) {

}

void *SetSearch(sortedset *set, const void *elemPtr) {
  int *indexPtr = findElem(set, elemPtr);
  int index = *indexPtr;
  if (index == -1) {
    return NULL;
  }
  void* elem = (char*)set->base + sizeof(int) + index*(set->elemSize + 2* sizeof(int));
  return elem;
}

bool SetAdd(sortedset *set, const void *elemPtr) {
  int *indexPtr = findElem(set, elemPtr);

  if (*indexPtr != -1) {
    return false;
  }

  *indexPtr = set->logLen;
  if (set->logLen >= set->allocLen) {
    set->allocLen *= 2;
    set->base = realloc(set->allocLen * (elemSize + 2 * sizeof(int)) + sizeof(int));
  }

  void *newElemAddr = (char *)set->base + sizeof(int) + set->logLen * (set->elemSize + 2 * sizeof(int));
  memcpy(newElemAddr, elemPtr, elemSize);

  (int*)((char*)newElemAddr + elemSize)[0] = -1;
  (int *)((char *)newElemAddress + elemSize)[1] = -1;

  set->logLen++;
}