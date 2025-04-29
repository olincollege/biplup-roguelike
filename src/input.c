#include "input.h"
#include "kinematics.h"
#include "object_utils.h"
#include "system_utils.h"
#include "text.h"
#include "tonc.h"
#include "types.h"

extern Game_State game_state;

void pregame_key_input() {
  key_poll();
  if (key_is_down(KEY_UP)) {
    reset_game_state();
  }
}

void game_key_input(Player *player) {
  key_poll();
  if (key_is_down(KEY_UP)) {
    update_jump_state(player);
  }
  // TODO: implement pokemon cheat here
}

void postgame_key_input(Obstacle **obstacles) {
  key_poll();
  if (key_is_down(KEY_UP)) {
    reset_game_state();
    restart_obstacles(obstacles);
  }
}
