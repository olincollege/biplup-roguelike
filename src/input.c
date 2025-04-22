#include "input.h"
#include "kinematics.h"
#include "text.h"
#include "tonc.h"
#include "utils.h"

void poll_key_input(Object *obj, int *game_state,
                    int *score) { // TODO: split into key-by-key functions
  key_poll();
  if (key_is_down(KEY_UP)) {
    switch (*game_state) {
    case 0: // not started
      reset_game_state(game_state, score);
      break;
    case 1: // gameplay
      update_jump_state(obj);
      break;
    case 2: // game over
      reset_game_state(game_state, score);
      break;
    }
  }
}
