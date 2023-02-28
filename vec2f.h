#pragma once

#include "int.h"

typedef struct _vec2f
{
  float x, y;
} vec2f_t;

vec2f_t *vec2f_set(vec2f_t *out, float x, float y);
vec2f_t *vec2f_reset(vec2f_t *out);
#ifdef MATH
vec2f_t *vec2f_polar(vec2f_t *out, float rotation, float length);
#endif
vec2f_t *vec2f_polari(vec2f_t *out, uint16_t rotation, float length);
float vec2f_length(vec2f_t *in);
vec2f_t *vec2f_add(vec2f_t *out, vec2f_t *a, vec2f_t *b);
vec2f_t *vec2f_add_scaled(vec2f_t *out, vec2f_t *a, vec2f_t *b, float scale);
vec2f_t *vec2f_subtract(vec2f_t *out, vec2f_t *a, vec2f_t *b);
vec2f_t *vec2f_multiply(vec2f_t *out, vec2f_t *a, vec2f_t *b);
vec2f_t *vec2f_scale(vec2f_t *out, vec2f_t *in, float scale);
vec2f_t *vec2f_divide(vec2f_t *out, vec2f_t *a, vec2f_t *b);
vec2f_t *vec2f_copy(vec2f_t *out, vec2f_t *in);
vec2f_t *vec2f_perp_left(vec2f_t *out, vec2f_t *in);
vec2f_t *vec2f_perp_right(vec2f_t *out, vec2f_t *in);
#ifdef MATH
vec2f_t *vec2f_rotate(vec2f_t *out, vec2f_t *in, float rotation);
#endif
vec2f_t *vec2f_rotatei(vec2f_t *out, vec2f_t *in, uint16_t rotation);
