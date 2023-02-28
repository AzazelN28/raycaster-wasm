#pragma once

#include "int.h"

typedef struct _backdrop
{
  uint32_t floor;
  uint32_t ceil;
} backdrop_t;

void backdrop_setup(backdrop_t *backdrop);
void backdrop_set_colors(backdrop_t *backdrop, uint32_t floor, uint32_t ceil);
