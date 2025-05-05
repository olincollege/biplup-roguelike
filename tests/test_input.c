#include "test_input.h"

#include "input.h"
#include "kinematics.h"
#include "object_utils.h"
#include "types.h"

#include "tonc.h"

#include <stdbool.h>

extern Game_State game_state;
extern int score;
extern int frame_counter;
extern int cheat_sprite_state;
extern u32 test_input;

void set_test_input(u32 input) { test_input = input; }

int test_pregame_reset_score() {
  game_state = PRE_GAME;
  score = 222;
  set_test_input(KEY_UP);
  get_input(KEY_UP);

  pregame_key_input();
  set_test_input(0);

  // Test if score was reset to 0
  if (score == 0) {
    return 1;
  }
  return 0;
}

int test_pregame_reset_frame() {
  game_state = PRE_GAME;
  frame_counter = 45;
  set_test_input(KEY_UP);
  get_input(KEY_UP);

  pregame_key_input();
  set_test_input(0);

  // Test if frame count was reset to 1
  if (frame_counter == 1) {
    return 1;
  }
  return 0;
}

int test_pregame_to_game() {
  game_state = PRE_GAME;
  set_test_input(KEY_UP);
  get_input(KEY_UP);

  pregame_key_input();
  set_test_input(0);

  // Test if game state was set to GAME
  if (game_state == GAME) {
    return 1;
  }
  return 0;
}

int test_jump_state() {
  game_state = GAME;
  Player *player = &(Player){0};
  player_constructor(player);
  player->jumping = false;
  set_test_input(KEY_UP);
  get_input(KEY_UP);

  game_key_input(player);
  set_test_input(0);

  // Test if game state was set to GAME
  if (player->jumping == true) {
    return 1;
  }
  return 0;
}

// for postgame_key_input()
int test_postgame_reset_score() {
  game_state = POST_GAME;
  score = 222;
  Obstacle *obst = &(Obstacle){0};
  set_test_input(KEY_UP);
  get_input(KEY_UP);

  postgame_key_input((Obstacle *[]){obst});
  set_test_input(0);

  // Test if score was reset to 0
  if (score == 0) {
    return 1;
  }
  return 0;
}

int test_postgame_reset_frame() {
  game_state = POST_GAME;
  frame_counter = 45;
  Obstacle *obst = &(Obstacle){0};
  obst->obj_args = &(Object){0};
  set_test_input(KEY_UP);
  get_input(KEY_UP);

  postgame_key_input((Obstacle *[]){obst});
  set_test_input(0);

  // Test if frame count was reset to 1
  if (frame_counter == 1) {
    return 1;
  }
  return 0;
}
int test_postgame_to_game() {
  game_state = POST_GAME;
  Obstacle *obst = &(Obstacle){0};
  set_test_input(KEY_UP);
  get_input(KEY_UP);

  postgame_key_input((Obstacle *[]){obst});
  set_test_input(0);

  // Test if game state was set to GAME
  if (game_state == GAME) {
    return 1;
  }
  return 0;
}
int test_postgame_obst_reset() {
  game_state = POST_GAME;

  // Set up obstacles
  Obstacle *obstacle_1 = &(Obstacle){};
  obstacle_1->obj_args = &(Object){};
  int initial_y = 10;
  int velocity = 10;
  int initial_x = 10;

  obstacle_constructor(obstacle_1, 1, initial_y, velocity, 50, BLOB);

  Obstacle *obstacle_2 = &(Obstacle){};
  obstacle_2->obj_args = &(Object){};

  obstacle_constructor(obstacle_2, 2, initial_y, velocity, 50, BLOB);

  Obstacle *obstacle_3 = &(Obstacle){};
  obstacle_3->obj_args = &(Object){};

  obstacle_constructor(obstacle_3, 3, initial_y, velocity, 50, BLOB);

  Obstacle *obstacle_4 = &(Obstacle){};
  obstacle_4->obj_args = &(Object){};

  obstacle_constructor(obstacle_4, 4, initial_y, velocity, 50, BLOB);

  Obstacle *obstacles[4] = {obstacle_1, obstacle_2, obstacle_3, obstacle_4};

  for (int i = 0; i < 4; i++) {
    obj_set_pos(obstacles[i]->obj_args->attr, initial_x, initial_y);
    obstacles[i]->obj_args->x = initial_x;
    obstacles[i]->obj_args->y = initial_y;
    spawn(obstacles[i]);
  }

  // Key input
  set_test_input(KEY_UP);
  get_input(KEY_UP);

  postgame_key_input(obstacles);
  set_test_input(0);

  // Test if obstacle is hidden and offscreen
  for (int i = 0; i > 3; i++) {
    if ((obstacles[i]->is_active != false) ||
        (obstacles[i]->obj_args->x != SCREEN_WIDTH + OFFSCREEN_OFFSET)) {
      return 0;
    }
  }
  return 1;
}

int test_cheat_mode_toggle() {
  game_state = GAME;
  Player *player = &(Player){0};
  player_constructor(player);
  Obstacle *obst = &(Obstacle){0};
  set_test_input(KEY_RIGHT);
  get_input(KEY_RIGHT);

  cheat_key_input(player, (Obstacle *[]){obst});
  set_test_input(0);

  // Test if the cheat sprite state is set to 1
  if (cheat_sprite_state == 1) {
    return 1;
  }
  return 0;
}
