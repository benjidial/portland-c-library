#include <stdint.h>

/*Written by Benji Dial
  PortlandCLib stdio.h*/

typedef struct {
  /*PFS driver structure*/
  uint16_t pos;
} FILE;

inline void putchar(uint8_t ch) {
  asm (
    "int $0x48"
  :: "al" (ch));
}

inline void puts(uint8_t *str) {
  asm (
    "int $0x4a\n"
    "mov $10, %al\n"
    "int $0x48"
  :: "ebx" (str) : "al");
}

inline uint8_t getchar(void) {
  uint8_t r;
  asm (
    "mov $0x00, %al\n"
    "int $0x50"
  : "=dl" (r) :: "al");
  return r;
}

inline uint8_t *gets(uint8_t *str, uint16_t max_size) {
  asm (
    "mov $0x00, %al\n"
    "int $0x52"
  :: "ebx" (str), "cx" (max_size) : "al");
  return str;
}

inline void remove(uint8_t *str) {
  asm (
    "int $0x45"
  :: "ebx" (str) : "al");
}

inline FILE *fopen(uint8_t *name) {
  FILE *r;
  asm (
    "mov ax, SIZE OF FILE STRUCTURE\n"
    "int $0x58\n"
    "int $0x43"
  : "=ebx" (r) : "edx" (name) : "al");
  r->pos = 0;
  return r;
}

inline void fclose(FILE *file) {
  asm (
    "int $0x59"
  :: "ebx" (file) : "al");
}

inline void fread(uint8_t *buffer, uint16_t length, FILE *file) {
  asm (
    "int $0x40"
  :: "ax" (file->pos), "ebx" (file), "cx" (length), "edx" (buffer) : "al");
  file->pos += length;
}

inline void fwrite(uint8_t *buffer, uint16_t length, FILE *file) {
  asm (
    "int $0x41"
  :: "ax" (file->pos), "ebx" (file), "cx" (length), "edx" (buffer) : "al");
  file->pos += length;
}
