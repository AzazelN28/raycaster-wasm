#pragma once

#include "int.h"
#include "backdrop.h"

#define SCREEN_WIDTH 320
#define SCREEN_HALF_WIDTH 160
#define SCREEN_HEIGHT 180
#define SCREEN_HALF_HEIGHT 90
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)
#define SCREEN_HALF_SIZE (SCREEN_WIDTH * SCREEN_HALF_HEIGHT)

void screen_clear(backdrop_t *backdrop);
void screen_box(int32_t sx, int32_t sy, int32_t ex, int32_t ey, uint32_t color);
void screen_put_pixel(int32_t x, int32_t y, uint32_t color);
