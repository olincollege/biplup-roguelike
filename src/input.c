#include "input.h"
#include "kinematics.h"
#include "object_utils.h"
#include "system_utils.h"
#include "text.h"
#include "tonc.h"
#include "types.h"

extern Game_State game_state;

void poll_key_input(
    Object *obj, Object **obstacles) { // TODO: split into key-by-key functions
  key_poll();
  if (key_is_down(KEY_UP)) {
    switch (game_state) {
    case PRE_GAME: // not started
      reset_game_state();
      break;
    case GAME: // gameplay
      update_jump_state(obj);
      break;
    case POST_GAME: // game over
      reset_game_state();
      restart_objects(obstacles);
      break;
    }
  }
}
