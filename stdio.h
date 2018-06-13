#include <stdint.h>

/*Copyright 2018 Benji Dial
  PortlandCLib stdio.h*/

inline void putchar(uint8_t ch) {
  asm volatile ("pushb %ch\nint 0x8d\naddw $1, %sp");
}

inline void puts(uint8_t *str) {
  asm volatile ("pushw %str\nint 0x8e\naddw $2, %sp");
  putchar('\n');
}
