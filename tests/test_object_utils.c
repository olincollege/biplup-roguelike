#include "test_object_utils.h"

#include "kinematics.h"
#include "object_utils.h"
#include "system_utils.h"
#include "tonc.h"
#include "types.h"
#include <stdbool.h>

#include "assets/blob.h"

// object constructor variables
int test_object_counter = 0;
float test_x = 0.0;
float test_y = 0.0;
Sprite_ID test_tile_number = DINO;
extern int cheat_sprite_state;

// obstacle constructor variables
float test_x_velocity = 1.0;
int test_frame_threshold = 1;

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
