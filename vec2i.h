#pragma once

#include "vec2f.h"

typedef struct _vec2i
{
  int32_t x, y;
} vec2i_t;

vec2i_t *vec2i_set(vec2i_t *out, int32_t x, int32_t y);
vec2i_t *vec2i_reset(vec2i_t *out);
vec2i_t *vec2i_copy(vec2i_t *out, vec2i_t *in);
vec2i_t *vec2i_floor(vec2i_t *out, vec2f_t *in);
vec2i_t *vec2i_ceil(vec2i_t *out, vec2f_t *in);
