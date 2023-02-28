#include "color.h"
#include "backdrop.h"

void backdrop_setup(backdrop_t* backdrop) {
  backdrop->floor = ABGR(0xFF, 0xFF, 0xFF, 0x00);
  backdrop->ceil = ABGR(0xFF, 0x00, 0xFF, 0xFF);
}

void backdrop_set_colors(backdrop_t* backdrop, uint32_t floor, uint32_t ceil)
{
  backdrop->floor = floor;
  backdrop->ceil = ceil;
}
