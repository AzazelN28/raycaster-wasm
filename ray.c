#include "int.h"
#include "math.h"
#include "level.h"
#include "ray.h"
#include "view.h"

void ray_update(ray_t *ray, view_t *view)
{
  vec2f_copy(&ray->position, &view->position);
}

void ray_cast(ray_t *ray, view_t *view, uint32_t *level, float x)
{
  ray->hit = 0;
  ray->side = RAY_SIDE_X;

  vec2i_copy(&ray->tile, &view->tile);
  vec2f_add_scaled(&ray->direction, &view->direction, &view->plane, (x - 0.5) * 2.0);

  ray->delta_dist.x = ABS(1.0 / ray->direction.x);
  ray->delta_dist.y = ABS(1.0 / ray->direction.y);

  if (ray->direction.x < 0.0)
  {
    ray->side_dist.x = (ray->position.x - ray->tile.x) * ray->delta_dist.x;
    ray->step.x = -1.0;
  }
  else
  {
    ray->side_dist.x = (ray->tile.x + 1.0 - ray->position.x) * ray->delta_dist.x;
    ray->step.x = 1.0;
  }

  if (ray->direction.y < 0.0)
  {
    ray->side_dist.y = (ray->position.y - ray->tile.y) * ray->delta_dist.y;
    ray->step.y = -1.0;
  }
  else
  {
    ray->side_dist.y = (ray->tile.y + 1.0 - ray->position.y) * ray->delta_dist.y;
    ray->step.y = 1.0;
  }

  while (!ray->hit)
  {
    if (ray->side_dist.x < ray->side_dist.y) {
      ray->side_dist.x += ray->delta_dist.x;
      ray->tile.x += ray->step.x;
      ray->side = RAY_SIDE_X;
    } else {
      ray->side_dist.y += ray->delta_dist.y;
      ray->tile.y += ray->step.y;
      ray->side = RAY_SIDE_Y;
    }

    int32_t x = ray->tile.x;
    int32_t y = ray->tile.y;
    if (x < 0 || x >= LEVEL_WIDTH || y < 0 || y >= LEVEL_HEIGHT)
    {
      ray->hit = 0;
      ray->side = RAY_SIDE_OUT;
      break;
    }

    uint32_t offset = y * LEVEL_WIDTH + x;
    if (level[offset] != 0)
    {
      ray->hit = 0;
      break;
    }
  }

  if (ray->side == RAY_SIDE_X)
  {
    ray->distance = ray->side_dist.x - ray->delta_dist.x;
    ray->x = ray->position.y + ray->distance * ray->direction.y;
  }
  else if (ray->side == RAY_SIDE_Y)
  {
    ray->distance = ray->side_dist.y - ray->delta_dist.y;
    ray->x = ray->position.x + ray->distance * ray->direction.x;
  }
  else
  {
    ray->distance = -1;
  }

  ray->x -= floor(ray->x);
}
