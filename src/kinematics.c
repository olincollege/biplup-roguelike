#include "kinematics.h"

#include "system_utils.h"
#include "types.h"

#include "tonc.h"

void update_obj_x(Object *obj) {
  int x_val = obj->attr->attr1 & 0x01FF;
  obj->x = x_val;
}

void update_obj_y(Object *obj) {
  int y_val = obj->attr->attr0 & 0x00FF;
  obj->y = y_val;
}

void reset_obstacle_position(Obstacle *obs) {
  obj_set_pos(obs->obj_args->attr, SCREEN_WIDTH + OFFSCREEN_OFFSET,
              obs->obj_args->y);
  update_obj_x(obs->obj_args);
}

void set_obstacle_x_velocity(Obstacle *obs, float x_velocity) {
  obs->x_velocity = x_velocity;
}

void set_player_y_velocity(Player *player, float y_velocity) {
  player->y_velocity = y_velocity;
}

void set_jump_state(Player *player, bool jumping) { player->jumping = jumping; }

void update_jump_state(Player *player) {
  // if the player isn't already jumping, set player jump to true and set player
  // y velocity to jump velocity
  if (!player->jumping) {
    set_player_y_velocity(player, PLAYER_Y_JUMP_VEL);
    set_jump_state(player, true);
  }
}

void update_player_physics(Player *player) {
  // compute player y velocity based on kinematics
  set_player_y_velocity(player, player->y_velocity + player->y_acceleration);
  // compute player's new y value based on kinematics
  float y_temp =
      player->obj_args->y +
      (player->y_velocity + PLAYER_Y_ACCEL_MOD * player->y_acceleration);
  // if the new y value is on the floor or going beneath the floor, set player's
  // y value to the floor and set player jump state to false
  if (y_temp >= FLOOR_LEVEL) {
    y_temp = FLOOR_LEVEL;
    set_jump_state(player, false);
  }
  // set player's new position
  obj_set_pos(player->obj_args->attr, (int)player->obj_args->x, (int)y_temp);
  update_obj_x(player->obj_args);
  update_obj_y(player->obj_args);
}
