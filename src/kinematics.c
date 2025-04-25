#include "kinematics.h"
#include "system_utils.h"
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

void reset_obstacle_position(Object *obs) {
  obj_set_pos(obs->attr, SCREEN_WIDTH + OFFSCREEN_OFFSET, obs->y);
  update_obj_x(obs);
}

void set_obstacle_x_velocity(Object *obs, float x_velocity) {
  obs->x_velocity = x_velocity;
}

void set_player_y_velocity(Object *player, float y_velocity) {
  player->y_velocity = y_velocity;
}

void set_obj_y_acceleration(Object *player, float y_acceleration) {
  player->y_acceleration = y_acceleration;
}

void set_jump_state(Object *player, bool jumping) { player->jumping = jumping; }

void update_jump_state(Object *player) {
  if (!player->jumping) {
    set_player_y_velocity(player, PLAYER_Y_JUMP_VEL);
    set_jump_state(player, true);
  }
}

void update_player_physics(Object *player) {
  set_player_y_velocity(player, player->y_velocity + player->y_acceleration);
  float y_temp = player->y + (player->y_velocity + 10 * player->y_acceleration);
  if (y_temp >= FLOOR_LEVEL) {
    y_temp = FLOOR_LEVEL;
    set_jump_state(player, false);
  }
  obj_set_pos(player->attr, (int)player->x, (int)y_temp);
  update_obj_x(player);
  update_obj_y(player);
}
