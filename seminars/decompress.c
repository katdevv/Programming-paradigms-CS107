#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Decompresses given RNE compressed data.
// Takes ownership of memory block pointed by passed data pointer.
// Char array pointed by data ends with ‘\0’.
// After returning data must be pointing to a memory block which contains decompressed
// information ownership of which is passed back to the caller.

void Decompress(char **data){
  char* compressed = *data;
  int log_len = 1; // output length so far (keep 1 for '\0')
  char* decompressed = malloc(log_len);
  *decompressed = 0; // start with empty C-string

  while(*compressed){
    char length_run = *compressed; // LLLLRRRR
    int run = length_run & 0b00001111; // right 4 bits 0b00001111 is a binary mask → 0000 1111 (decimal 15).
    // shifts the whole byte right by 4 bits, so the left 4 bits move into the lower half.
    int length = (length_run >> 4) & 0b00001111; // left 4 bits

    log_len += length * run; // grows in size
    decompressed = realloc(decompressed, log_len);

    for (int i = 0; i < run; i++){
      // append exactly 'length' bytes from after the control byte
      // strncat(destination, source, n) appends at most n bytes from source to the end of the destination string (and adds '\0' automatically).
      strncat(decompressed, compressed + 1, length);
    }
    // advance input: skip the control byte + the literal segment
    compressed += length + 1;
  }
  *data = decompressed; // hand back the newly allocated decompressed string
}
