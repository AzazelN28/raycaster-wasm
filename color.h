#pragma once

#include "int.h"

#define RGBA(r, g, b, a) (r << 24) | (g << 16) | (b << 8) | (a & 0xFF)
#define ARGB(a, r, g, b) (a << 24) | (r << 16) | (g << 8) | (b & 0xFF)
#define ABGR(a, b, g, r) (a << 24) | (b << 16) | (g << 8) | (r & 0xFF)

uint32_t color_create(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
