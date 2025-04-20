#include "move.h"

#include "tonc.h"

int check_obj_overlap(const Object *obj1, const Object *obj2) {
  // features of object 1
  int obj1_x = obj1->x;
  int obj1_y = obj1->y;
  int obj1_width = 10;  // obj_get_width(obj1->attr);
  int obj1_height = 10; // obj_get_height(obj1->attr);

  // features of object 2
  int obj2_x = obj2->x;
  int obj2_y = obj2->y;
  int obj2_width = 10;  // obj_get_width(obj2->attr);
  int obj2_height = 10; // obj_get_height(obj2->attr);

  // AABB collision detection
  int not_right = obj1_x < obj2_x + obj2_width;
  int not_left = obj1_x + obj1_width > obj2_x;
  int not_below = obj1_y < obj2_y + obj2_height;
  int not_above = obj1_y + obj1_height > obj2_y;
  if (not_right && not_left && not_below && not_above) {
    return 1;
  }

  return 0;
}

void check_obj_offscreen(const Object *obj, direction *dir) {

  dir->left = 0;
  dir->right = 0;
  dir->top = 0;
  dir->bottom = 0;

  // features of object
  int obj_x = obj->x;
  int obj_y = obj->y;
  int obj_width = 10;  // obj_get_width(obj->attr);
  int obj_height = 10; // obj_get_height(obj->attr);

  // left/right
  if (obj_x - obj_width > SCREEN_WIDTH) {
    dir->right = 1;
  }
  if (obj_x + obj_width < 0) {
    dir->left = 1;
  }

  // up/down
  if (obj_y - obj_height > SCREEN_HEIGHT) {
    dir->bottom = 1;
  }
  if (obj_y + obj_height < 0) {
    dir->top = 1;
  }
}
