#include "view.h"
#include "vec2f.h"

void view_setup(view_t *view)
{
  view->rotation = 0;

  vec2f_set(&view->position, 1.5, 1.5);
  vec2f_set(&view->direction, 1.0, 0.0);
  vec2f_set(&view->plane, 0.0, 0.66);
  vec2f_set(&view->strafe, 0.0, 1.0);

  vec2i_floor(&view->tile, &view->position);
}

void view_update(view_t *view)
{
  vec2f_polari(&view->direction, view->rotation, 1.0);

  vec2f_perp_right(&view->plane, &view->direction);
  vec2f_scale(&view->plane, &view->plane, 0.66);

  vec2f_perp_right(&view->strafe, &view->direction);

  vec2i_floor(&view->tile, &view->position);

  // Requerido para hacer transformaciones de matriz correctas.
  view->inv_det = 1.0 / (view->plane.x * view->direction.y - view->direction.x * view->plane.y);
}
