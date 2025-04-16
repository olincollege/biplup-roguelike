#include "player_movement.h"

void set_obj_x(Object *obj, int x) {
  obj->attr->attr1 = ATTR1_X(x) | ATTR1_SIZE_16x16;
  obj->x = x;
}

void set_obj_y(Object *obj, int y) {
  obj->attr->attr0 = ATTR0_Y(y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG;
  obj->y = y;
}

void set_obj_x_velocity(Object *obj, float x_velocity) {
  obj->x_velocity = x_velocity;
}

void set_obj_y_velocity(Object *obj, float y_velocity) {
  obj->y_velocity = y_velocity;
}

void set_obj_x_acceleration(Object *obj, float x_acceleration) {
  obj->x_acceleration = x_acceleration;
}

void set_obj_y_acceleration(Object *obj, float y_acceleration) {
  obj->y_acceleration = y_acceleration;
}

void set_jumping(Object *obj, bool jumping) { obj->jumping = jumping; }

void key_input(Object *obj) {
  key_poll();
  if (!obj->jumping) {
    if (key_is_down(KEY_UP)) {
      set_obj_y_velocity(obj, -10);
      set_jumping(obj, true);
    }
  }
}

void update_physics(Object *obj) {
  set_obj_y_velocity(obj, obj->y_velocity += obj->y_acceleration);
  set_obj_y(obj, obj->y += (obj->y_velocity + 0.5 * obj->y_acceleration));
}
