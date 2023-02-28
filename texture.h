#pragma once

#include "int.h"

#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64
#define TEXTURE_SIZE (TEXTURE_WIDTH * TEXTURE_HEIGHT)
#define MAX_TEXTURES 2048

typedef struct _texture
{
  uint32_t data[TEXTURE_SIZE];
} texture_t;
