#include "test_input.h"

#include "input.h"
#include "kinematics.h"
#include "object_utils.h"
#include "tonc.h"
#include "types.h"
#include <stdbool.h>

extern Game_State game_state;
extern int score;
extern int frame_counter;
extern int cheat_sprite_state;

int test_pregame_reset_score() {
  game_state = PRE_GAME;
  score = 222;
  pregame_key_input();

  // Simulating pressing the up button
  u16 simulated_input = 0x03BF;
  u16 key_curr = ~simulated_input;

  // Test if score was reset to zero
  if (score == 0) {
    return 1;
  }
  return 0;
}

int test_pregame_reset_frame() {
  game_state = PRE_GAME;
  frame_counter = 45;
  pregame_key_input();

  // Simulating pressing the up button
  u16 simulated_input = 0x03BF;
  u16 key_curr = ~simulated_input;

  // Test if frame count was reset to 1
  if (frame_counter == 1) {
    return 1;
  }
  return 0;
}

int test_pregame_to_game() {
  game_state = PRE_GAME;
  pregame_key_input();

  // Simulating pressing the up button
  u16 simulated_input = 0x03BF;
  u16 key_curr = ~simulated_input;

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
  player->jumping == false;

  game_key_input(player);

  // Simulating pressing the up button
  u16 simulated_input = 0x03BF;
  u16 key_curr = ~simulated_input;

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
  postgame_key_input((Obstacle *[]){obst});

  // Simulating pressing the up button
  u16 simulated_input = 0x03BF;
  u16 key_curr = ~simulated_input;

  // Test if score was reset to zero
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
  postgame_key_input((Obstacle *[]){obst});

  // Simulating pressing the up button
  u16 simulated_input = 0x03BF;
  u16 key_curr = ~simulated_input;

  // Test if frame count was reset to 1
  if (frame_counter == 1) {
    return 1;
  }
  return 0;
}
int test_postgame_to_game() {
  game_state = POST_GAME;
  Obstacle *obst = &(Obstacle){0};
  postgame_key_input((Obstacle *[]){obst});

  // Simulating pressing the up button
  u16 simulated_input = 0x03BF;
  u16 key_curr = ~simulated_input;

  // Test if game state was set to GAME
  if (game_state == GAME) {
    return 1;
  }
  return 0;
}
int test_postgame_obst_reset() {
  game_state = POST_GAME;
  Obstacle *obst = &(Obstacle){0};
  postgame_key_input((Obstacle *[]){obst});

  // Simulating pressing the up button
  u16 simulated_input = 0x03BF;
  u16 key_curr = ~simulated_input;

  // Test if obstacle is hidden and offscreen
  if ((obst->is_active == false) &&
      (obst->obj_args->x == SCREEN_WIDTH + OFFSCREEN_OFFSET)) {
    return 1;
  }
  return 0;
}

int test_cheat_mode_toggle() {
  game_state = GAME;
  Player *player = &(Player){0};
  player_constructor(player);
  Obstacle *obst = &(Obstacle){0};
  postgame_key_input((Obstacle *[]){obst});

  cheat_key_input(player, (Obstacle *[]){obst});

  // Simulating pressing the right button
  u16 simulated_input = 0x03EF;
  u16 key_curr = ~simulated_input;

  // Test if the cheat sprite state is set to 1
  if (cheat_sprite_state == 1) {
    return 1;
  }
  return 0;
}
