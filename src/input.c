#include "input.h"
#include "kinematics.h"
#include "object_utils.h"
#include "system_utils.h"
#include "text.h"
#include "tonc.h"
#include "types.h"

extern Game_State game_state;
extern int score;
extern u32 test_input;

u32 get_input(u32 key) {
  key_poll();
  return key_is_down(key) | test_input;
}

void pregame_key_input() {
  u32 input = get_input(KEY_UP);
  if (input == KEY_UP) {
    reset_game_state();
  }
}

void game_key_input(Player *player) {
  u32 input = get_input(KEY_UP);
  if (input == KEY_UP) {
    update_jump_state(player);
  }
}

void postgame_key_input(Obstacle **obstacles) {
  u32 input = get_input(KEY_UP);
  if (input == KEY_UP) {
    reset_game_state();
    restart_obstacles(obstacles);
  }
}

void cheat_key_input(Player *player, Obstacle **obstacles) {
  u32 input = get_input(KEY_RIGHT);
  if (input == KEY_RIGHT) {
    cheat_toggle_pokemon(player, obstacles);
  }
}
