#pragma once

#include "tonc.h"
#include "types.h"
#include <stdbool.h>

void update_obj_x(Object *obj);
void update_obj_y(Object *obj);
void despawn(Object *obj);
void set_obj_x_velocity(Object *obj, float x_velocity);
void set_obj_y_velocity(Object *obj, float y_velocity);
void set_obj_x_acceleration(Object *obj, float x_acceleration);
void set_obj_y_acceleration(Object *obj, float y_acceleration);
void set_jumping(Object *obj, bool jumping);
void key_input(Object *obj);
void update_physics(Object *obj, int min_y_val);
void despawn(Object *obj);
void spawn(Object *obj);
void set_obj_beginning(Object *obj);