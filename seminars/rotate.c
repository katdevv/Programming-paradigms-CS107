// the region [start, middle) is moved after [middle, end)
// It rotates two adjecent chunks of memory
void rotate(void* start, void* middle, void* end){
  int left = (char*)middle - (char*)start;
  int right = (char*)end - (char*)middle;
  void* tmp = malloc(right);
  assert(tmp != NULL);
  memcpy(tmp, (char*)start + left, right); // sad, ra, ramdenit
  // memmove(destination, source, n_bytes)
  // copies n_bytes from source → destination.
  memmove((char*) start + right, start, left);
  memcpy(start, tmp, right);
  free(tmp);
}