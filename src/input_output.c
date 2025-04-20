#include "input_output.h"
#include "text.h" // start_game should eventually be moved to a model file
#include "tonc.h"

void poll_key_input(Object *obj, int *game_state, int *score) {
  key_poll();
  if (key_is_down(KEY_UP)) {
    switch (*game_state) {
    case 0: // not started
      start_game(game_state, score);
    case 1: // gameplay
      set_obj_y_velocity(obj, -10);
      set_jumping(obj, true);
    case 2: // game over
      start_game(game_state, score);
    }
  }
}
