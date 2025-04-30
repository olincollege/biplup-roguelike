#include "test_object_utils.h"

#include "object_utils.h"
#include "tonc.h"
#include "types.h"
#include <stdbool.h>

#include "assets/blob.h"

int test_right_offscreen() {
  Object *object = &(Object){};
  float offscreen_x = 240 + 32 + 1;
  RECT direction;
  object_constructor(object, 1, offscreen_x, 10.0, BLOB);

  check_obj_offscreen(object, &direction);

  return direction.right == 1;
}
