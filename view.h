#pragma once

#include "vec2f.h"
#include "vec2i.h"
#include "int.h"

typedef struct _view
{
  vec2f_t position;
  vec2f_t direction;
  vec2f_t strafe;
  vec2f_t plane;
  vec2i_t tile;
  uint16_t rotation;
  float inv_det;
} view_t;

void view_setup(view_t *view);
void view_update(view_t *view);
