#include "test_object_utils.h"

#include "kinematics.h"
#include "object_utils.h"
#include "system_utils.h"
#include "tonc.h"
#include "types.h"
#include <stdbool.h>

#include "assets/blob.h"

extern int cheat_sprite_state;

// object constructor variables
int test_object_counter = 0;
float test_x = 0.0;
float test_y = 0.0;
Sprite_ID test_tile_number = DINO;

// obstacle constructor variables
float test_x_velocity = 1.0;
int test_frame_threshold = 1;

int test_object_constructor() {
  Object *test_obj = &(Object){0};
  object_constructor(test_obj, test_object_counter, test_x, test_y,
                     test_tile_number);

  // evaluate all properties
  return test_obj->object_counter == test_object_counter &&
         test_obj->x == test_x && test_obj->y == test_y &&
         test_obj->default_sprite == test_tile_number;
}

int test_obstacle_constructor() {
  Obstacle *test_obs = &(Obstacle){0};
  test_obs->obj_args = &(Object){0};

  obstacle_constructor(test_obs, test_object_counter, test_y, test_x_velocity,
                       test_frame_threshold, test_tile_number);

  // evaluate all properties
  return test_obs->x_velocity == test_x_velocity &&
         test_obs->frame_spawn_threshold == test_frame_threshold &&
         test_obs->is_active == false &&
         test_obs->obj_args->x == SCREEN_WIDTH + OFFSCREEN_OFFSET;
}

int test_player_constructor() {
  Player *test_player = &(Player){0};
  test_player->obj_args = &(Object){0};

  player_constructor(test_player);

  return test_player->obj_args->object_counter == 0 &&
         test_player->obj_args->x == PLAYER_X_POS &&
         test_player->obj_args->y == FLOOR_LEVEL &&
         test_player->obj_args->default_sprite == DINO &&
         test_player->y_velocity == 0 &&
         test_player->y_acceleration == PLAYER_Y_ACCEL &&
         test_player->jumping == false;
}

int test_despawn_hide() {
  Obstacle *test_obs = &(Obstacle){0};
  test_obs->obj_args = &(Object){0};

  obstacle_constructor(test_obs, test_object_counter, test_y, test_x_velocity,
                       test_frame_threshold, test_tile_number);
  despawn(test_obs);

  return BFN_GET(test_obs->obj_args->attr->attr0, ATTR0_MODE) == ATTR0_HIDE;
}

int test_despawn_inactive() {
  Obstacle *test_obs = &(Obstacle){0};
  test_obs->obj_args = &(Object){0};

  obstacle_constructor(test_obs, test_object_counter, test_y, test_x_velocity,
                       test_frame_threshold, test_tile_number);
  despawn(test_obs);

  return !test_obs->is_active;
}

int test_spawn_show() {
  Obstacle *test_obs = &(Obstacle){0};
  test_obs->obj_args = &(Object){0};

  obstacle_constructor(test_obs, test_object_counter, test_y, test_x_velocity,
                       test_frame_threshold, test_tile_number);
  spawn(test_obs);

  return BFN_GET(test_obs->obj_args->attr->attr0, ATTR0_MODE) == 0;
}

int test_spawn_active() {
  Obstacle *test_obs = &(Obstacle){0};
  test_obs->obj_args = &(Object){0};

  obstacle_constructor(test_obs, test_object_counter, test_y, test_x_velocity,
                       test_frame_threshold, test_tile_number);
  spawn(test_obs);

  return test_obs->is_active;
}

int test_right_offscreen() {
  Object *object = &(Object){};
  float offscreen_x = 240 + 32 + 1;
  RECT direction;
  object_constructor(object, 1, offscreen_x, 10.0, BLOB);

  check_obj_offscreen(object, &direction);

  return direction.right == 1;
}

int test_toggle_cheat_state_on() {
  // cheat_sprite_state starts off as off (0) as the cheat_toggle_pokemon will
  // toggle it on
  cheat_sprite_state = 0;

  // create test obstacle
  // note: test_obs will have the default sprite id of DINO
  Obstacle *test_obs = &(Obstacle){0};
  test_obs->obj_args = &(Object){0};

  obstacle_constructor(test_obs, test_object_counter, test_y, test_x_velocity,
                       test_frame_threshold, test_tile_number);

  Obstacle *test_obstacles[1] = {test_obs};

  // create test player
  // note: test_player will have the default sprite id of DINO
  Player *test_player = &(Player){0};
  test_player->obj_args = &(Object){0};
  player_constructor(test_player);

  cheat_toggle_pokemon(test_player, test_obstacles);

  // cheat_toggle_pokemon should set both test_player and test_obs sprite id to
  // BIPLUP
  return (get_sprite_id(test_player->obj_args) == BIPLUP) &&
         (get_sprite_id(test_obs->obj_args) == BIPLUP);
}
