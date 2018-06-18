#include <stdint.h>

/*Written by Benji Dial
  PortlandCLib stdio.h*/

typedef struct {
  uint8_t file_id;
  uint16_t length;
  uint16_t position;
  uint8_t *contents;
} FILE;
typedef uint16_t FILE_POS_T;

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

inline void remove(uint8_t *str) {
  asm volatile (
    "pushw %str\n"
    "int $0x97\n"
    "addw $2, %sp"
  );
}

inline FILE *fopen(uint8_t *name) {
  FILE *r;
  asm volatile (
    "pushw %name\n"
    "int $0x90\n"
    "addw $2, %sp"
  : "=a" (r));
  return r;
}

inline void fclose(FILE *file) {
  asm volatile (
    "pushw %file\n"
    "int $0x96\n"
    "int $0x91\n"
    "addw $2, %sp"
  );
}

inline void fread(uint8_t *buffer, size_t length, FILE *file) {
  asm volatile (
    "pushw %buffer\n"
    "pushw %length\n"/*Assuming size_t is 16-bit*/
    "pushw %file\n"
    "int $0x93\n"
    "addw $6, %sp"
  );
}

inline void fwrite(uint8_t buffer, size_t length, FILE *file) {
  asm volatile (
    "pushw %buffer\n"
    "pushw %length\n"/*Assuming size_t is 16-bit*/
    "pushw %file\n"
    "int $0x94\n"
    "addw $6, %sp"
  );
}

inline void fsetpos(FILE *file, FILE_POS_T position) {
  asm volatile (
    "pushw %position\n"/*Assuming FILE_POS_T is 16-bit*/
    "pushw %file\n"
    "int 0x92\n"
    "addw $4, %sp"
  );
}

inline void rewind(FILE *file) {
  fsetpos(file, 0);
}
