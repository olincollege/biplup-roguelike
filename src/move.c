#include "move.h"

#include "tonc.h"

int check_obj_overlap(const Object *obj1, const Object *obj2)
{
  // features of object 1
  int ax = obj1->x;
  int ay = obj1->y;
  int aw = obj_get_width(obj1->attr);
  int ah = obj_get_height(obj1->attr);

  // features of object 2
  int bx = obj2->x;
  int by = obj2->y;
  int bw = obj_get_width(obj2->attr);
  int bh = obj_get_height(obj2->attr);

  // AABB collision detection
  if (
      ax < bx + bw &&
      ax + aw > bx &&
      ay < by + bh &&
      ay + ah > by)
  {
    return 1;
  }

  return 0;
}

void check_obj_offscreen(const Object *obj, direction *dir)
{

  dir->left = 0;
  dir->right = 0;
  dir->top = 0;
  dir->bottom = 0;

  // features of object
  int ax = obj->x;
  int ay = obj->y;
  int aw = obj_get_width(obj->attr);
  int ah = obj_get_height(obj->attr);

  // left/right
  if (ax - aw > SCREEN_WIDTH)
  {
    dir->right = 1;
  }
  if (ax + aw < 0)
  {
    dir->left = 1;
  }

  // up/down
  if (ay - ah > SCREEN_HEIGHT)
  {
    dir->bottom = 1;
  }
  if (ay + ah < 0)
  {
    dir->top = 1;
  }
}
