#pragma once

#include "vec2f.h"
#include "vec2i.h"
#include "view.h"

#define RAY_SIDE_X     0
#define RAY_SIDE_Y     1
#define RAY_SIDE_OUT   2

typedef struct _ray
{
  vec2f_t position;
  vec2f_t direction;
  vec2i_t tile;
  vec2f_t step;
  vec2f_t delta_dist;
  vec2f_t side_dist;
  float x;
  float distance;
  int side;
  int hit;
} ray_t;

void ray_update(ray_t *ray, view_t *view);
void ray_cast(ray_t *ray, view_t *view, unsigned int *level, float x);
