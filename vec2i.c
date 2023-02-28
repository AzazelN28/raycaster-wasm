#include "vec2i.h"
#include "vec2f.h"

vec2i_t *vec2i_set(vec2i_t *out, int32_t x, int32_t y) {
  out->x = x;
  out->y = y;
  return out;
}

vec2i_t *vec2i_reset(vec2i_t *out) {
  return vec2i_set(out, 0, 0);
}

vec2i_t *vec2i_copy(vec2i_t *out, vec2i_t *in)
{
  return vec2i_set(out, in->x, in->y);
}

vec2i_t *vec2i_floor(vec2i_t *out, vec2f_t *in)
{
  return vec2i_set(out, (int32_t)(in->x), (int32_t)(in->y));
}

vec2i_t *vec2i_ceil(vec2i_t *out, vec2f_t *in)
{
  return vec2i_set(out, ceil(in->x), ceil(in->y));
}
