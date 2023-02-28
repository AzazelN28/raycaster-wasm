#include "int.h"
#include "backdrop.h"
#include "screen.h"

uint32_t screen[SCREEN_SIZE];

void screen_clear(backdrop_t *backdrop)
{
  for (int32_t i = 0; i < SCREEN_SIZE; i++)
  {
    if (i < SCREEN_HALF_SIZE)
    {
      // Techo
      screen[i] = backdrop->ceil;
    }
    else
    {
      // Suelo
      screen[i] = backdrop->floor;
    }
  }
}

void screen_box(int32_t sx, int32_t sy, int32_t ex, int32_t ey, uint32_t color)
{
  for (int32_t y = sy; y < ey; y++)
  {
    uint32_t base_offset = y * SCREEN_WIDTH;
    for (int32_t x = sx; x < ex; x++)
    {
      uint32_t offset = base_offset + x;
      screen[offset] = color;
    }
  }
}

void screen_put_pixel(int32_t x, int32_t y, uint32_t color)
{
  if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
  {
    return;
  }
  uint32_t offset = y * SCREEN_WIDTH + x;
  screen[offset] = color;
}
