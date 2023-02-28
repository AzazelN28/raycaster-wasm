#include "int.h"
#include "vec2f.h"
#include "trigs.h"

vec2f_t *vec2f_set(vec2f_t *out, float x, float y)
{
  out->x = x;
  out->y = y;
  return out;
}

vec2f_t *vec2f_reset(vec2f_t *out)
{
  return vec2f_set(out, 0, 0);
}

#ifdef MATH
vec2f_t *vec2f_polar(vec2f_t *out, float rotation, float length)
{
  return vec2f_set(
    out,
    cos(rotation) * length,
    sin(rotation) * length
  );
}
#endif

vec2f_t *vec2f_polari(vec2f_t *out, uint16_t rotation, float length)
{
  return vec2f_set(
    out,
    COS(rotation) * length,
    SIN(rotation) * length
  );
}

float vec2f_length(vec2f_t *in)
{
  return hypot(in->x, in->y);
}

vec2f_t *vec2f_add(vec2f_t *out, vec2f_t *a, vec2f_t *b)
{
  return vec2f_set(out, a->x + b->x, a->y + b->y);
}

vec2f_t *vec2f_add_scaled(vec2f_t *out, vec2f_t *a, vec2f_t *b, float scale)
{
  return vec2f_set(out, a->x + b->x * scale, a->y + b->y * scale);
}

vec2f_t *vec2f_subtract(vec2f_t *out, vec2f_t *a, vec2f_t *b)
{
  return vec2f_set(out, a->x - b->x, a->y - b->y);
}

vec2f_t *vec2f_multiply(vec2f_t *out, vec2f_t *a, vec2f_t *b)
{
  return vec2f_set(out, a->x * b->x, a->y * b->y);
}

vec2f_t *vec2f_scale(vec2f_t *out, vec2f_t *in, float scale)
{
  return vec2f_set(out, in->x * scale, in->y * scale);
}

vec2f_t *vec2f_divide(vec2f_t *out, vec2f_t *a, vec2f_t *b)
{
  return vec2f_set(out, a->x / b->x, a->y / b->y);
}

vec2f_t *vec2f_copy(vec2f_t *out, vec2f_t *in)
{
  return vec2f_set(out, in->x, in->y);
}

vec2f_t *vec2f_perp_left(vec2f_t *out, vec2f_t *in)
{
  return vec2f_set(out, in->y, -in->x);
}

vec2f_t *vec2f_perp_right(vec2f_t *out, vec2f_t *in)
{
  return vec2f_set(out, -in->y, in->x);
}

#ifdef MATH
vec2f_t *vec2f_rotate(vec2f_t *out, vec2f_t *in, float rotation)
{
  float c = cos(rotation);
  float s = sin(rotation);
  return vec2f_set(
    out,
    in->x * c - in->y * s,
    in->x * s + in->y * c
  );
}
#endif

vec2f_t *vec2f_rotatei(vec2f_t *out, vec2f_t *in, uint16_t rotation)
{
  float c = COS(rotation);
  float s = SIN(rotation);
  return vec2f_set(
    out,
    in->x * c - in->y * s,
    in->x * s + in->y * c
  );
}
