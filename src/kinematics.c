#include "kinematics.h"
#include "tonc.h"
#include "types.h"

void update_obj_x(Object *obj) {
  int x_val = obj->attr->attr1 & 0x01FF;
  obj->x = x_val;
}

void update_obj_y(Object *obj) {
  int y_val = obj->attr->attr0 & 0x00FF;
  obj->y = y_val;
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

void set_jump_state(Object *obj, bool jumping) { obj->jumping = jumping; }

void update_jump_state(Object *obj) {
  if (!obj->jumping) {
    set_obj_y_velocity(obj, -10);
    set_jump_state(obj, true);
  }
}

void update_physics(Object *obj, int min_y_val) {
  set_obj_y_velocity(obj, obj->y_velocity + obj->y_acceleration);
  float y_temp = obj->y + (obj->y_velocity + 10 * obj->y_acceleration);
  if (y_temp >= min_y_val) {
    y_temp = min_y_val;
    set_jump_state(obj, false);
  }
  obj_set_pos(obj->attr, (int)obj->x, (int)y_temp);
  update_obj_x(obj);
  update_obj_y(obj);
}
