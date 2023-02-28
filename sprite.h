#pragma once

#include "box.h"
#include "vec2f.h"
#include "vec2i.h"

#define MAX_SPRITES 1024

typedef struct _sprite
{
  float distance;
  uint32_t texture;
  int32_t rel;
  uint32_t order;
  uint16_t rotation;
  vec2f_t position;
  vec2f_t delta;
  vec2f_t transform;
  vec2i_t screen;
  vec2i_t screen_size;
  vec2i_t screen_half_size;
  vec2f_t size;
  vec2i_t tile;
  box_t box;
} sprite_t;

