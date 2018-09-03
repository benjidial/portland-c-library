#include <stdint.h>

/*Written by Benji Dial
  The Portland C Library*/

inline uint8_t file_read(uint16_t start, file_t *file, uint16_t size, uint8_t *buffer) {
  uint8_t ret;
  asm (
    "int $0x40"
    : "=a" (ret)
    : "a" (start),
      "b" (file),
      "c" (size),
      "d" (buffer)
    : /*TODO: clobber*/
  );
  return ret;
}

inline uint8_t file_write(uint16_t start, file_t *file, uint16_t size, uint8_t *buffer) {
  uint8_t ret;
  asm (
    "int $0x41"
    : "=a" (ret)
    : "a" (start),
      "b" (file),
      "c" (size),
      "d" (buffer)
    : /*TODO: clobber*/
  );
  return ret;
}

inline uint8_t file_create(uint8_t res, file_t *file, uint16_t size, uint8_t *name) {
  uint8_t ret;
  asm (
    "int $0x42"
    : "=a" (ret)
    : "a" (res),
      "b" (file),
      "c" (size),
      "d" (name)
    : /*TODO: clobber*/
  );
  return ret;
}

inline uint8_t file_open(file_t *file, uint8_t *name) {
  uint8_t ret;
  asm (
    "int $0x43"
    : "=a" (ret)
    : "b" (file),
      "d" (name)
    : /*TODO: clobber*/
  );
  return ret;
}

/*TODO: file_resize*/

inline uint8_t file_delete(uint8_t *name) {
  uint8_t ret;
  asm (
    "int $0x45"
    : "=a" (ret)
    : "b" (name)
    : /*TODO: clobber*/
  );
  return ret;
}

inline uint8_t file_exec(uint8_t *name, uint32_t *retValPtr) {
  uint8_t ret;
  asm (
    "int $0x46"
    : "=a" (ret),
      "=d" (*retValPtr)
    : "b" (name)
    : /*TODO: clobber*/
  );
  return ret;
}

inline uint8_t file_info(file_info_t *file_info, uint8_t *name) {
  uint8_t ret;
  asm (
    "int $0x47"
    : "=a" (ret)
    : "b" (file_info),
      "d" (name)
    : /*TODO: clobber*/
  );
  return ret;
}

inline void print_byte(uint8_t byte) {
  asm (
    "int $0x48"
    :
    : "a" (byte)
    : "ebx"
  );
}

inline void print_word(uint16_t word) {
  asm (
    "int $0x49"
    :
    : "a" (word)
    : "ebx"
  );
}

inline uint8_t print_bytes(uint8_t *bytes) {
  uint8_t ret;
  asm (
    "int $0x4a"
    : "=a" (ret)
    : "b" (bytes)
    : "ah", "ebx", "edx"
  );
  return ret;
}

inline uint8_t print_words(uint16_t *words) {
  uint8_t ret;
  asm (
    "int $0x4b"
    : "=a" (ret)
    : "b" (words)
    : "ah", "ebx", "edx"
  );
  return ret;
}

inline void clear_screen(void) {
  asm (
    "int $0x4c"
    :
    :
    : "ax", "ebx"
  );
}

inline void set_color(uint8_t color) {
  asm (
    "int $0x4d"
    :
    : "a" (color)
    :
  );
}

inline void move_cursor(uint8_t row, uint8_t column) {
  asm (
    "int $0x4e"
    :
    : "a" ((uint16_t)((uint16_t)column * 256 + row))
    : "ax", "dl"
  );
}
