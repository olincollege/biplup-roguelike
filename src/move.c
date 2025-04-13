#include "move.h"
#include "tonc.h"
#include "util.h"

int check_obj_overlap(const OBJ_ATTR *obj1, const OBJ_ATTR *obj2) {
  // features of object 1
  int ax = OBJ_X(obj1);
  int ay = OBJ_Y(obj1);
  int aw = obj_get_width(obj1);
  int ah = obj_get_height(obj1);

  // features of object 2
  int bx = OBJ_X(obj2);
  int by = OBJ_Y(obj2);
  int bw = obj_get_width(obj2);
  int bh = obj_get_height(obj2);

  // AABB collision detection
  if (ax < bx + bw && ax + aw > bx && ay < by + bh && ay + ah > by) {
    return 1;
  }

  return 0;
}

dir *check_obj_offscreen(const OBJ_ATTR *obj1) {
  // features of object
  int ax = OBJ_X(obj1);
  int ay = OBJ_Y(obj1);
  int aw = obj_get_width(obj1);
  int ah = obj_get_height(obj1);

  dir *offscreen_result = malloc(sizeof(dir));
  // left/right
  if (SCREEN_WIDTH < ax + aw) {
    offscreen_result->right = 1;
  } else if (ax < SCREEN_WIDTH) {
    offscreen_result->left = 1;
  }

  // up/down
  if (SCREEN_HEIGHT < ay + ah) {
    offscreen_result->up = 1;
  } else if (ay < SCREEN_HEIGHT) {
    offscreen_result->down = 1;
  }

  return offscreen_result;
}
