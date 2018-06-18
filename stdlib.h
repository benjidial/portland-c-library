#include <stdint.h>

/*Written by Benji Dial
  PortlandCLib stdlib.h*/

inline void *calloc(uint16_t size) {
  void *r = malloc(size);
  uint8_t *i, *e = (i = r - 1) + size;
  while ((++i) < e)
    *i = 0x00;
  return r;
}

inline void *malloc(uint16_t size) {
  void *r;
  asm volatile (
    "pushw %size\n"
    "int $0x80\n"
    "addw $2, %sp"
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

inline void system(uint8_t *path) {
  asm volatile (
    "pushw %path\n"
    "int $0x95\n"
    "addw $2, %sp"
  );
}
