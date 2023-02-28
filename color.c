#include "int.h"

uint32_t color_create(
  uint8_t r,
  uint8_t g,
  uint8_t b,
  uint8_t a
) {
  return (r << 24) | (g << 16) | (b << 8) | a;
}
