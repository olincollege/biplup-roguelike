#include "tonc.h"

#include "input.h"
#include "kinematics.h"
#include "object_utils.h"
#include "system_utils.h"
#include "text.h"
#include "types.h"

#include <stdbool.h>
#include <stdlib.h>

extern Game_State game_state;
extern int frame_counter;

int main(void) {
  init_main();

  Object *obstacles[OBSTACLE_AMOUNT];

  // player
  Object *player = &(Object){};
  player_constructor(player, 0, 40, FLOOR_LEVEL, BLOB);
  update_obj_x(player);
  update_obj_y(player);

  construct_obstacles(obstacles);

  while (true) {
    // sync up the video
    vid_vsync();

    // the whole game is wrapped into a switch-case based on game state
    switch (game_state) {
    case PRE_GAME: { // game has not started
      poll_key_input(NULL, NULL);
      break;
    }
    case GAME: { // main game

      // receive player input and update physics
      poll_key_input(player, NULL);
      update_physics(player, FLOOR_LEVEL);

      // allow each object to move, spawn, or wait
      for (int i = 0; i < OBSTACLE_AMOUNT; i++) {
        update_obstacle(obstacles[i]);
      }

      // check if the player is colliding with each object
      if (!check_player_collision(player, obstacles)) {
        // score update
        if (frame_counter % 5 == 0) {
          score_update();
        }
      } else {
        // game ending consequence
        end_game();
      }
      // while loop loops is equivalent to amount of frames displayed
      frame_counter++;
      break;
    }
    case POST_GAME: {
      end_text();
      poll_key_input(NULL, obstacles);
      break;
    }
    }
  }
  return EXIT_SUCCESS;
}
