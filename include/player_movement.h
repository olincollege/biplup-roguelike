#pragma once

#include "tonc.h"
#include <stdbool.h>

typedef struct object_t {
  OBJ_ATTR *attr;
  float x;
  float y;
  float x_velocity;
  float y_velocity;
  float x_acceleration;
  float y_acceleration;
  bool jumping;
} Object;

void set_obj_x(Object *obj, int x);
void set_obj_y(Object *obj, int y);
void set_obj_x_velocity(Object *obj, float x_velocity);
void set_obj_y_velocity(Object *obj, float y_velocity);
void set_obj_x_acceleration(Object *obj, float x_acceleration);
void set_obj_y_acceleration(Object *obj, float y_acceleration);
void set_jumping(Object *obj, bool jumping);
void key_input(Object *obj);
void update_physics(Object *obj);
