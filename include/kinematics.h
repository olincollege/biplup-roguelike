#pragma once

#include "tonc.h"
#include "types.h"
#include <stdbool.h>

#define PLAYER_X_POS 40
#define PLAYER_Y_JUMP_VEL -10
#define PLAYER_Y_ACCEL 0.5
#define OBSTACLE_X_VELOCITY 1.5

void update_obj_x(Object *obj);
void update_obj_y(Object *obj);
void set_obj_x_velocity(Object *obj, float x_velocity);
void set_obj_y_velocity(Object *obj, float y_velocity);
void set_obj_x_acceleration(Object *obj, float x_acceleration);
void set_obj_y_acceleration(Object *obj, float y_acceleration);
void set_jump_state(Object *obj, bool jumping);
void update_jump_state(Object *obj);
void update_physics(Object *obj, int min_y_val);
