#include <stdint.h>

/*Copyright 2018 Benji Dial
  PortlandCLib stdio.h*/

inline void putchar(uint8_t ch) {
  asm volatile (
    "pushb %ch\n"
    "int $0x8d\n"
    "addw $1, %sp"
  );
}

inline void puts(uint8_t *str) {
  asm volatile (
    "pushw %str\n"
    "int $0x8e\n"
    "addw $2, %sp"
  );
  putchar('\n');
}

inline uint8_t getchar(void) {
  uint8_t r;
  asm volatile (
    "pushb $0x01\n"
    "int $0x99\n"
    "addw $1, %sp"
  : "=a" (r));
  return r;
}

inline uint8_t *gets(uint8_t *str) {
  asm volatile (
    "pushb $0x01"
    "pushw %str\n"
    "int $0x9a\n"
    "addw $3, %sp"
  );
  return str;
}
