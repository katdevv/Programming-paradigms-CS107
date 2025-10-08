// API - constract - interface
typedef void(*FreeFn)(void*);
// defines a function pointer (callback) type

// A callback function is just a function pointer that you pass to
// another function so that it can “call you back” later when it needs to
// perform some action.


// typedef → we’re defining a new type alias called FreeFn
// void (*FreeFn)(void*) → means “a pointer to a function that
// takes one void* parameter and returns nothing”
// FreeFn is a type for a function pointer and assign it a real function that matches the same signature.

//*FreeFn is a pointer to a function that takes one void* argument
//and returns nothing (void)

// Typedef here is syntatic sugar to avoid defining vars like this: struct Stack a;
typedef struct {
  void* base;
  int elem_size;
  int log_len;
  int alloc_len;
  FreeFn free_fn;
} Stack;

void StackInit(Stack* s, int elem_size, FreeFn free_fn);
void StackDestroy(Stack* s);

// Takes ownership of the given memory
void StackPush(Stack* s, void* v);

// Gives ownership of the returned memory to the client
void StackPop(Stack* s, void* addr);
int StackSize(Stack* s);