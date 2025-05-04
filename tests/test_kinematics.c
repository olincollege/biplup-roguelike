#include "test_kinematics.h"
#include "kinematics.h"
#include "system_utils.h"
#include "tonc.h"
#include "types.h"

int test_reset_obstacle_position() {
  Obstacle *obs = &(Obstacle){0};
  obs->obj_args = &(Object){0};

  obstacle_constructor(obs, 1, FLOOR_LEVEL - 10, DACTYL_BASE_X_VELOCITY, 200,
                       DACTYL);

  reset_obstacle_position(obs);

  return obs->obj_args->x == (SCREEN_WIDTH + OFFSCREEN_OFFSET);
}

int test_set_obstacle_x_velocity() {
  Obstacle *obs = &(Obstacle){0};
  obs->obj_args = &(Object){0};

  obstacle_constructor(obs, 1, FLOOR_LEVEL - 10, DACTYL_BASE_X_VELOCITY, 200,
                       DACTYL);

  set_obstacle_x_velocity(obs, 3);

  return obs->x_velocity == 3;
}

int test_set_player_y_velocity() {
  Player *player = &(Player){0};
  player->obj_args = &(Object){0};
  player_constructor(player);
  set_player_y_velocity(player, -12);

  return player->y_velocity == -12;
}

int test_set_jump_state() {
  Player *player = &(Player){0};
  player->obj_args = &(Object){0};
  player_constructor(player);
  set_jump_state(player, true);

  return player->jumping == true;
}

int test_update_jump_state_starts_jump() {
  Player *player = &(Player){0};
  player->obj_args = &(Object){0};
  player_constructor(player);
  update_jump_state(player);

  return player->jumping == true && player->y_velocity == PLAYER_Y_JUMP_VEL;
}

int test_update_jump_state_while_jumping() {
  Player *player = &(Player){0};
  player->obj_args = &(Object){0};
  player_constructor(player);

  // makes player jump
  update_jump_state(player);

  // this should not change anything as player is already jumping
  update_jump_state(player);

  return player->y_velocity == PLAYER_Y_JUMP_VEL && player->jumping == true;
}

int test_update_player_physics() {
  Player *player = &(Player){0};
  player->obj_args = &(Object){0};
  player_constructor(player);

  // simulating player jump and checking if player properly falls down from it
  update_jump_state(player);
  // looping checks to see if player gets stuck in midair indefinitely
  for (int i = 0; i < 30; i++) {
    update_player_physics(player);
    // checks to see if player touches ground
    if (player->obj_args->x == FLOOR_LEVEL) {
      // checks if player's jump state is set back to false
      return !player->jumping;
    }
  }
  return 0;
}
