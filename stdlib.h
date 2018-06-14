#include <stdint.h>

/*Copyright 2018 Benji Dial
  PortlandCLib stdlib.h*/

#define MEM_BLOCK_SIZE /*TODO*/

inline void *calloc(void) {
  void *r = malloc();
  uint16_t *i, *e = (i = (uint16_t)r - 2) + MEM_BLOCK_SIZE; /*Assuming MEM_BLOCK_SIZE even*/
  while ((i += 2) < e)
    *i = 0x0000;
  return r;
}

inline void *malloc(void) {
  void *r;
  asm volatile (
    "int $0x80"
  : "=a" (r));
  return r;
}

inline void free(void *block) {
  asm volatile (
    "pushw %block\n"
    "int $0x81\n"
    "addw $2, %sp"
  );
}
