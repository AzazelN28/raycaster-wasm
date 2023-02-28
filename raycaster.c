#include "math.h"
#include "ray.h"
#include "view.h"
#include "screen.h"
#include "level.h"
#include "backdrop.h"
#include "sprite.h"
#include "texture.h"
#include "color.h"
#include "int.h"
#include "bool.h"

#define PLAYER_RADIUS 0.5

texture_t textures[MAX_TEXTURES];
uint32_t level[LEVEL_SIZE];
sprite_t sprites[MAX_SPRITES];
float zbuffer[SCREEN_WIDTH];

backdrop_t backdrop;
ray_t ray;
view_t view;

bool sprite_set_tile(uint32_t index, int32_t x, int32_t y)
{
  if (x < 0 || y < 0 || x >= LEVEL_WIDTH || y >= LEVEL_HEIGHT)
  {
    return false;
  }
  vec2i_set(&sprites[index].tile, x, y);
  vec2f_set(&sprites[index].position, (float)x + 0.5, (float)y + 0.5);
  return true;
}

bool is_walkable(int32_t x, int32_t y)
{
  uint32_t offset = y * LEVEL_WIDTH + x;
  return level[offset] == 0;
}

bool set_tile(int32_t x, int32_t y)
{
  if (x < 0 || y < 0 || x >= LEVEL_WIDTH || y >= LEVEL_HEIGHT)
  {
    return false;
  }
  vec2i_set(&view.tile, x, y);
  vec2f_set(&view.position, (float)x + 0.5, (float)y + 0.5);
  return true;
}

void set_rotation(uint16_t rotation)
{
  view.rotation = rotation;
}

void turn_left(uint16_t quantity)
{
  view.rotation -= quantity;
}

void turn_right(uint16_t quantity)
{
  view.rotation += quantity;
}

bool move_by(float quantity, bool perp)
{
  vec2f_t direction;
  vec2f_t next_position;
  vec2i_t next_tile;
  vec2f_polari(&direction, view.rotation, quantity);
  if (perp)
  {
    vec2f_perp_left(&direction, &direction);
  }

  // Necesito implementar sliding walls.
  vec2f_add(&next_position, &view.position, &direction);
  vec2i_floor(&next_tile, &next_position);
  if (!is_walkable(next_tile.x, next_tile.y))
  {
    return false;
  }

  vec2f_copy(&view.position, &next_position);
  return true;
}

bool move_forward(float quantity)
{
  return move_by(quantity, false);
}

bool move_backward(float quantity)
{
  return move_by(-quantity, false);
}

bool strafe_by(float quantity)
{
  return move_by(quantity, true);
}

bool strafe_left(float quantity)
{
  return strafe_by(quantity);
}

bool strafe_right(float quantity)
{
  return strafe_by(-quantity);
}

void sprites_setup()
{
  sprite_t *sprite;
  for (uint32_t index = 0; index < MAX_SPRITES; index++)
  {
    sprite = &sprites[index];
    vec2f_set(&sprite->size, 1, 1);
  }
}

void setup()
{
  backdrop_setup(&backdrop);
  view_setup(&view);
  sprites_setup();
}

void update()
{
  // Limpiamos el fondo.
  screen_clear(&backdrop);

  // actualizamos la vista.
  view_update(&view);

  // coordenada de la pantalla.
  ray_update(&ray, &view);
  for (int32_t x = 0; x < SCREEN_WIDTH; x++)
  {
    ray_cast(&ray, &view, level, (float)x / (float)SCREEN_WIDTH);

    // escribimos en el zbuffer la distancia a la que chocó el rayo.
    zbuffer[x] = ray.distance;

    int32_t column_height = (int32_t)(SCREEN_HEIGHT / ray.distance);
    int32_t column_half_height = column_height >> 1;

    int32_t sy = SCREEN_HALF_HEIGHT - column_half_height;
    int32_t ey = SCREEN_HALF_HEIGHT + column_half_height;
    for (int32_t y = sy; y < ey; y++)
    {
      if (ray.side == RAY_SIDE_X)
      {
        screen_put_pixel(x, y, ABGR(0xFF, 0xFF, 0x00, 0xFF));
      }
      else if (ray.side == RAY_SIDE_Y)
      {
        screen_put_pixel(x, y, ABGR(0xFF, 0x77, 0x00, 0x77));
      }
      else
      {
        screen_put_pixel(x, y, ABGR(0xFF, 0xFF, 0x00, 0xFF));
      }
    }
  }

  sprite_t *sprite;
  // Calculamos las distancias de los sprites.
  for (uint32_t i = 0; i < MAX_SPRITES; i++)
  {
    sprite = &sprites[i];

    sprite->order = i;
    sprite->distance = ((view.position.x - sprite->position.x) * (view.position.x - sprite->position.x) + (view.position.y - sprite->position.y) * (view.position.y - sprite->position.y));
  }

  // TODO: Aquí hace falta realizar el sorting de los sprites.

  // después de ordenar los sprites, hacer la proyección y dibujarlos.
  for (uint32_t i = 0; i < MAX_SPRITES; i++)
  {
    uint32_t order = i;

    sprite = &sprites[order];

    sprite->delta.x = sprite->position.x - view.position.x;
    sprite->delta.y = sprite->position.y - view.position.y;

    // Transformar el sprite con la matriz inversa de la cámara.
    //  [ planeX   dirX ] -1                                       [ dirY      -dirX ]
    //  [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
    //  [ planeY   dirY ]                                          [ -planeY  planeX ]

    sprite->transform.x = view.inv_det * (view.direction.y * sprite->delta.x - view.direction.x * sprite->delta.y);
    // Esto es en realidad la profundidad dentro de la pantalla, que lo que Z es en 3D,
    // la distancia del sprite al jugador, igualando sqrt(spriteDistance[i])
    sprite->transform.y = view.inv_det * (-view.plane.y * sprite->delta.x + view.plane.x * sprite->delta.y);
    sprite->screen.x = (int32_t)(SCREEN_HALF_WIDTH * (1 + sprite->transform.x / sprite->transform.y));

/*
#define vMove 0.0

    int32_t vMoveScreen = (int32_t)(vMove / sprite->transform.y);
*/

    sprite->rel = ABS((int32_t)(SCREEN_HEIGHT / (sprite->transform.y)));

    // Calculamos el alto en pantalla.
    sprite->screen_size.y = sprite->rel / sprite->size.x;
    sprite->screen_half_size.y = sprite->screen_size.y >> 1;

    // Calculamos el ancho del sprite.
    // Igual que la altura dado que son cuadrados. Esto se podría cambiar utilizando
    // los atributos u y v.
    sprite->screen_size.x = sprite->rel / sprite->size.y;
    sprite->screen_half_size.x = sprite->screen_size.x >> 1;

    // Esta es la caja del sprite en pixeles, puede ser útil para poder
    // detectar clicks en pantalla.
    sprite->box.start.y = CLAMP(-sprite->screen_half_size.y + SCREEN_HALF_HEIGHT /* + vMoveScreen */, 0, SCREEN_HEIGHT - 1);
    sprite->box.end.y = CLAMP(sprite->screen_half_size.y + SCREEN_HALF_HEIGHT /* + vMoveScreen */, 0, SCREEN_HEIGHT - 1);
    sprite->box.start.x = CLAMP(-sprite->screen_half_size.x + sprite->screen.x, 0, SCREEN_WIDTH);
    sprite->box.end.x = CLAMP(sprite->screen_half_size.x + sprite->screen.x, 0, SCREEN_WIDTH);

    // Está detrás de la cámara.
    if (sprite->transform.y < 0)
    {
      continue;
    }

    // pintamos las barras del sprite
    for (int32_t x = sprite->box.start.x; x < sprite->box.end.x; x++)
    {
      // si la profundidad del sprite es mayor que el del zbuffer (es decir,
      // de las paredes) entonces esta linea no se debe pintar.
      if (sprite->transform.y > zbuffer[x])
      {
        continue;
      }

      for (int32_t y = sprite->box.start.y; y < sprite->box.end.y; y++)
      {
        screen_put_pixel(x, y, ABGR(0xFF, 0xFF, 0xFF, 0xFF));
      }
      /*
      int32_t texX = (int32_t)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
      // the conditions in the if are:
      // 1) it's in front of camera plane so you don't see things behind you
      // 2) ZBuffer, with perpendicular distance
      if (transformY > 0 && transformY < zbuffer[stripe])
      {
        for (int y = drawStartY; y < drawEndY; y++) // for every pixel of the current stripe
        {
          int d = (y - vMoveScreen) * 256 - h * 128 + spriteHeight * 128; // 256 and 128 factors to avoid floats
          int texY = ((d * texHeight) / spriteHeight) / 256;
          Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; // get current color from the texture
          if ((color & 0x00FFFFFF) != 0)
            buffer[y][stripe] = color; // paint pixel if it isn't black, black is the invisible color
        }
      }
      */
    }
  }
}
