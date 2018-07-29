#include <stdint.h>

/*Written by Benji Dial
  PortlandCLib stdlib.h*/

inline void *calloc(uint16_t size) {
  void *r;
  asm (
    "int $0x58\n"
    "mov %ebx, %edx\n"
    ".loop:\n"
    "cmpw $4, %ax\n"
    "jl .done\n"
    "xord (%ebx), (%ebx)\n"
    "addd $4, %ebx\n"
    "subw $4, %ax\n"
    "jmp .loop\n"
    ".done:"
    "cmpw $0, %ax\n"
    "je .ret\n"
    "xorb (%ebx), (%ebx)\n"
    "cmpw $1, %ax\n"
    "je .ret\n"
    "xorb (%ebx)1, (%ebx)1\n"
    "compw $2, %ax\n"
    "je .ret\n"
    "xorb (%ebx)2, (%ebx)2\n"
    ".ret:"
  : "=edx" (r) : "ax" (size) : "ax", "ebx");
  return r;
}

inline void *malloc(uint16_t size) {
  void *r;
  asm (
    "int $0x58"
  : "=ebx" (r) : "ax" (size));
  return r;
}

inline void free(void *start) {
  asm (
    "int $0x59"
  :: "ebx" (start) : "al");
}

inline uint32_t system(uint8_t *filename) {
  uint32_t r;
  asm (
    "int $0x46"
  : "=edx" (r) : "ebx" (filename) : "al");
  return r;
}
