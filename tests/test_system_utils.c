#include "test_system_utils.h"

#include "system_utils.h"
#include "types.h"

#include "tonc.h"

#include <stdbool.h>

extern int score;
extern u32 high_score;
extern Game_State game_state;
extern RECT offscreen;
extern int frame_counter;
extern int end_game_frame;
extern int last_cheat_frame;
extern int animation_frame;
extern int cheat_sprite_state;

int test_init_main(void) {
  score = 100;
  high_score = 10000;
  game_state = POST_GAME;
  frame_counter = 1591;
  end_game_frame = 2;
  last_cheat_frame = 3;
  animation_frame = 4;
  cheat_sprite_state = 5;

  init_main();

  return score == 0 && high_score == retrieve_high_score() &&
         game_state == PRE_GAME && frame_counter == 1 && end_game_frame == 0 &&
         last_cheat_frame == 0 && animation_frame == 0 &&
         cheat_sprite_state == 0;
}

int test_reset_game_state(void) {

  high_score = 100;
  score = 500;
  game_state = POST_GAME;
  frame_counter = 15815;
  end_game_frame = 4;
  last_cheat_frame = 5;
  animation_frame = 6;

  reset_game_state();

  return high_score == (u32)500 && score == 0 && frame_counter == 1 &&
         game_state == GAME && end_game_frame == 0 && last_cheat_frame == 0 &&
         animation_frame == 0;
}

int test_retrieve_high_score(void) { return retrieve_high_score() == (u32)0; }
